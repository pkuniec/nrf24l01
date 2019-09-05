
#ifndef NRF24L01_MEM_H
#define NRF24L01_MEM_H


/* REGISTERS */
#define CONFIG      0x00
#define EN_AA       0x01
#define EN_RXADDR   0x02
#define SETUP_AW    0x03
#define SETUP_RETR  0x04
#define RF_CH       0x05
#define RF_SETUP    0x06
#define STATUS      0x07
#define OBSERVE_TX  0x08
#define RPD         0x09
#define RX_ADDR_P0  0x0A
#define RX_ADDR_P1  0x0B
#define RX_ADDR_P2  0x0C
#define RX_ADDR_P3  0x0D
#define RX_ADDR_P4  0x0E
#define RX_ADDR_P5  0x0F
#define TX_ADDR     0x10
#define RX_PW_P0	0x11
#define RX_PW_P1	0x12
#define RX_PW_P2	0x13
#define RX_PW_P3	0x14
#define RX_PW_P4	0x15
#define RX_PW_P5	0x16
#define FIFO_STATUS 0x17
#define DYNPD       0x1C
#define FEATURE     0x1D


/* CONFIG */
#define MASK_RX_DR       0x40
#define MASK_TX_DS       0x20
#define MASK_MAX_RT      0x10
#define EN_CRC           0x08
#define CRC0             0x04
#define PWR_UP           0x02
#define PRIM_RX          0x01


/* EN AA */
#define ENAA_P5     	 0x20
#define ENAA_P4     	 0x10
#define ENAA_P3     	 0x08
#define ENAA_P2     	 0x04
#define ENAA_P1     	 0x02
#define ENAA_P0     	 0x01


/* EN RXADDR */
#define ERX_P5           0x20
#define ERX_P4           0x10
#define ERX_P3           0x08
#define ERX_P2           0x04
#define ERX_P1           0x02
#define ERX_P0           0x01


/* SETUP AW */
#define AW_3          0x01
#define AW_4          0x02
#define AW_5          0x03


/* SETUP RETR */
#define WAIT_4000uS   0xF0
#define WAIT_3750uS   0xE0
#define WAIT_3500uS   0XD0
#define WAIT_3250uS   0xC0
#define WAIT_3000uS   0xB0
#define WAIT_2750uS   0xA0
#define WAIT_2500uS   0x90
#define WAIT_2225uS   0x80
#define WAIT_2000uS   0x70
#define WAIT_1750uS   0x60
#define WAIT_1500uS   0x50
#define WAIT_1250uS   0x40
#define WAIT_1000uS   0x30
#define WAIT_750uS    0x20
#define WAIT_500uS    0x10
#define WAIT_250uS    0x00

#define RETR_15_TIMES 0x0F
#define RETR_14_TIMES 0x0E
#define RETR_13_TIMES 0x0D
#define RETR_12_TIMES 0x0C
#define RETR_11_TIMES 0x0B
#define RETR_10_TIMES 0x0A
#define RETR_9_TIMES  0x09
#define RETR_8_TIMES  0x08
#define RETR_7_TIMES  0x07
#define RETR_6_TIMES  0x06
#define RETR_5_TIMES  0x05
#define RETR_4_TIMES  0x04
#define RETR_3_TIMES  0x03
#define RETR_2_TIMES  0x02
#define RETR_1_TIME   0x01
#define RETR_0_TIMES  0X00


/* RF SETUP */
#define CONT_WAVE        0x80
#define RF_DR_LOW        0x20
#define RF_DR_HIGH       0x08
#define PLL_LOCK         0x10

#define RF_PWR_18dB        ( (0<<1) | (0<<2) )
#define RF_PWR_12dB        ( (0<<1) | (1<<2) )
#define RF_PWR_6dB         ( (1<<1) | (0<<2) )
#define RF_PWR_0dB         ( (1<<1) | (1<<2) )

#define TRANS_SPEED_2MB    ( (0<<5) | (1<<3) )
#define TRANS_SPEED_1MB    ( (0<<5) | (0<<3) )
#define TRANS_SPEED_250kB  (1<<5)


/* STATUS */
#define RX_DR       0x40
#define TX_DS       0x20
#define MAX_RT      0x10
#define TX_FULL     0x01

#define RX_PIPE_0   ( (0<<3) | (0<<2) | (0<<1) )
#define RX_PIPE_1   ( (0<<3) | (0<<2) | (1<<1) )
#define RX_PIPE_2   ( (0<<3) | (1<<2) | (0<<1) )
#define RX_PIPE_3   ( (0<<3) | (1<<2) | (1<<1) )
#define RX_PIPE_4   ( (1<<3) | (0<<2) | (0<<1) )
#define RX_PIPE_5   ( (1<<3) | (0<<2) | (1<<1) )
#define RX_P_EMPTY  ( (1<<3) | (1<<2) | (1<<1) )


/* OBSERVE TX */
#define PLOS_CNT    0xF0
#define ARC_CNT     0x0F


/* FIFO STATUS */
#define TX_REUSE    6
#define FULL_TX     5
#define TX_EMPTY    4
#define RX_FULL     1
#define RX_EMPTY    0


/* DYNPD */
#define DPL_P5		(1<<5)
#define DPL_P4		(1<<4)
#define DPL_P3		(1<<3)
#define DPL_P2		(1<<2)
#define DPL_P1		(1<<1)
#define DPL_P0		(1<<0)


/* FEATURE */
#define EN_DPL      2
#define EN_ACK_PAY  1
#define EN_DYN_ACK  0


/* COMMANDS */
#define W_ACK_PAYLOAD        0xA8
#define R_REGISTER           0x00
#define W_REGISTER           0x20
#define REGISTER_MASK        0x1F
#define R_RX_PAYLOAD         0x61
#define W_TX_PAYLOAD  		 0xA0
#define FLUSH_TX     		 0xE1
#define FLUSH_RX     		 0xE2
#define REUSE_TX_PL  		 0xE3
#define W_TX_PAYLOAD_NOACK	 0xB0
#define NOP                  0xFF
#define R_RX_PL_WID          0x60

#endif