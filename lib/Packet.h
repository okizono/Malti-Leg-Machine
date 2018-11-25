typedef struct {
public:
	void put(uint8_t data) {
		if(this->data == 0x00 && data == 0xff) {
			idx = 0;
			rcvd = 1;
		}
		this->data = data;
		if(rcvd > 0) {
			buf[idx] = data;
			idx++;
		} else {
			return;
		}
		if(idx == 0) {
			num = data >> 4;
			permit = (data & 0x04) >> 2;
			motor = (data & 0x01);
			if(data & 0x02) {
				motor *= -1;
			}
		}
		if(idx == 1) {
			power = data;
		}
		if(idx == 3) {
			angle1 = buf[2];
			angle1 <<= 8;
			angle1 |= buf[3];
		}
		if(idx == 5) {
			angle2 = buf[4];
			angle2 <<= 8;
			angle2 |= buf[5];
		}
	};
	uint8_t* createPacket(uint8_t* length) {
		uint8_t len = 0;
		packet[0] = 0x00;
		packet[1] = 0xff;
		uint8_t ms;
		if((motor & 0x7f) > 0) {
			ms = 1;
		}
		if((motor & 0x80) > 0) {
			ms |= 0x20;
		}
		packet[2] = (num << 4) | (permit << 2) | ms;
		packet[3] = power;
		packet[4] = (uint8_t)(angle1 >> 8);
		packet[5] = (uint8_t)angle1;
		packet[6] = (uint8_t)(angle2 >> 8);
		packet[7] = (uint8_t)angle2;
	}
	bool isReady() {
		return ready;
	}
	bool isPermit() {
		return permit;
	};
	int16_t getAngle1() {
		return angle1;
	};
	int16_t getAngle2() {
		return angle2;
	};
	int8_t getMotorStatus() {
		return motor;
	};
	uint8_t getMotorPower() {
		return power;
	};
	uint8_t buf[10];
	uint8_t packet[10];
	bool permit = 0;
	int8_t num = 0;
	int16_t angle1 = 0;
	int16_t angle2 = 0;
	int8_t motor = 0;
	uint8_t power = 0;
private:
	uint8_t data;
	uint8_t idx = 0;
	bool rcvd = 0;
	bool ready = 0;
} Packet;

/*
 * header 16bit(0000000011111111)
 * number 8bit
 *          4bit 番号
 *          1bit なし 0
 *          1bit 返信許可
 *          2bit モータ状態
 * power  8bit モーター出力
 * angle  16bit 先頭ビットが1のときマイナス * 2
 * led    8bit LED状態
 * 
 */
