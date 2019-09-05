#ifndef NRF24L01__H
#define NRF24L01__H


#define SPI_CE		PIN_3
#define SPI_CSN		PIN_2
#define NRF_IRQ		PIN_4

#define PAYLOADSIZE	5

#define min(a,b) ({ typeof (a) _a = (a); typeof (b) _b = (b); _a < _b ? _a : _b; })
#define max(a,b) ({ typeof (a) _a = (a); typeof (b) _b = (b); _a > _b ? _a : _b; })


typedef void (*nrf_cb_f)(void);

typedef struct {
	volatile uint8_t status;
	uint8_t pipe_no;
	uint8_t data_rx[PAYLOADSIZE];
	uint8_t len;
	nrf_cb_f func;	
} nrf_t;


extern nrf_t sys_nrf;


void nrf_init_hw(void);
void nrf_init_sw(void);
void nrf_reset(void);
void nrf_rx_enable(void);
void nrf_tx_enable(void);
void nrf_powerdown(void);
void nrf_csn_enable(void);
void nrf_csn_disable(void);
void nrf_ce_low(void);
void nrf_ce_high(void);
void nrf_checkstatus(void);
void nrf_register_cb(nrf_cb_f func);
void nrf_transmit(uint8_t *data);
void nrf_write_tx(uint8_t *data, uint8_t len);
void nrf_read_rx(uint8_t *data, uint8_t len);
uint8_t nrf_sendcmd(uint8_t cmd);
uint8_t nrf_readreg(uint8_t reg);
void nrf_writereg(uint8_t reg, uint8_t data);
void nrf_writereg_many(uint8_t cmd, uint8_t reg, uint8_t *data, uint8_t len);

#endif
