// 'battery', 37x21px
const unsigned char battery[] PROGMEM = {
    0x3f, 0xff, 0xff, 0xff, 0x80, 0x7f, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xe0,
    0x00, 0x00, 0x00, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0xf8, 0xe0, 0x00,
    0x00, 0x00, 0xf8, 0xe0, 0x00, 0x00, 0x00, 0x38, 0xe0, 0x00, 0x00, 0x00, 0x38, 0xe0, 0x00, 0x00,
    0x00, 0x38, 0xe0, 0x00, 0x00, 0x00, 0x38, 0xe0, 0x00, 0x00, 0x00, 0x38, 0xe0, 0x00, 0x00, 0x00,
    0x38, 0xe0, 0x00, 0x00, 0x00, 0x38, 0xe0, 0x00, 0x00, 0x00, 0xf8, 0xe0, 0x00, 0x00, 0x00, 0xf8,
    0xe0, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x7f,
    0xff, 0xff, 0xff, 0xc0, 0x3f, 0xff, 0xff, 0xff, 0x80};

// 'celsius', 26x20px
const unsigned char celsius[] PROGMEM = {
    0x3f, 0x80, 0x1f, 0xc0, 0x7f, 0xc0, 0x3f, 0xc0, 0xc0, 0x60, 0x60, 0x00, 0xc0, 0x60, 0x60, 0x00,
    0xc0, 0x60, 0x60, 0x00, 0xc0, 0x60, 0x60, 0x00, 0xc0, 0x60, 0x60, 0x00, 0xc0, 0x60, 0x60, 0x00,
    0xc0, 0x60, 0x60, 0x00, 0xff, 0xc0, 0x40, 0x00, 0x7f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00,
    0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x60, 0x00,
    0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x7f, 0xc0, 0x00, 0x00, 0x3f, 0xc0};

// 'steps', 19x23px
const unsigned char steps[] PROGMEM = {
    0x00, 0x03, 0xc0, 0x00, 0x07, 0xe0, 0x00, 0x07, 0xe0, 0x00, 0x0f, 0xe0, 0x78, 0x0f, 0xe0, 0xfc,
    0x0f, 0xe0, 0xfc, 0x0f, 0xe0, 0xfc, 0x0f, 0xe0, 0xfe, 0x0f, 0xe0, 0xfe, 0x07, 0xc0, 0xfe, 0x07,
    0xc0, 0xfe, 0x07, 0x80, 0xfe, 0x00, 0x00, 0x7c, 0x0e, 0x00, 0x7c, 0x0f, 0x80, 0x7c, 0x1f, 0x80,
    0x20, 0x1f, 0x00, 0x06, 0x0f, 0x00, 0x3e, 0x0e, 0x00, 0x3e, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x1e,
    0x00, 0x00, 0x1e, 0x00, 0x00};

// 'cloudsun', 48x32px
const unsigned char cloudsun[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x84, 0x40, 0x00, 0x00, 0x00, 0x10, 0x44, 0x42, 0x00, 0x00, 0x00, 0x08, 0x00, 0x04, 0x00, 0x00,
    0x00, 0x04, 0x00, 0x08, 0x00, 0x00, 0x00, 0x02, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0,
    0x00, 0x00, 0x00, 0x31, 0x80, 0x61, 0x00, 0x07, 0xe0, 0x19, 0x00, 0x32, 0x00, 0x38, 0x38, 0x02,
    0x00, 0x10, 0x00, 0x60, 0x04, 0x02, 0x00, 0x10, 0x00, 0x80, 0x03, 0xf2, 0x00, 0x10, 0x01, 0x00,
    0x01, 0x9e, 0x00, 0x10, 0x03, 0x00, 0x00, 0x03, 0x00, 0x10, 0x02, 0x00, 0x00, 0x01, 0x80, 0x10,
    0x02, 0x00, 0x00, 0x00, 0x80, 0x32, 0x04, 0x00, 0x00, 0x00, 0x40, 0x61, 0x04, 0x00, 0x00, 0x00,
    0x70, 0xc0, 0x0c, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x30, 0x00, 0x00, 0x00, 0x02, 0x08, 0x60, 0x00,
    0x00, 0x00, 0x01, 0x04, 0x40, 0x00, 0x00, 0x00, 0x01, 0xc2, 0x40, 0x00, 0x00, 0x00, 0x00, 0xc0,
    0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00,
    0x00, 0x80, 0x40, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x00, 0x00, 0x00, 0x01, 0x00, 0x20, 0x00,
    0x00, 0x00, 0x03, 0x00, 0x10, 0x00, 0x00, 0x00, 0x06, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xfc, 0x00};
// 'cloudy', 48x32px
const unsigned char cloudy[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x18, 0x03, 0x00, 0x00, 0x00,
    0x00, 0x60, 0x00, 0x80, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x40, 0x00, 0x00, 0x01, 0x80, 0x00, 0x3f,
    0xc0, 0x00, 0x01, 0x00, 0x00, 0x00, 0x30, 0x00, 0x02, 0x00, 0x00, 0x00, 0x18, 0x00, 0x02, 0x00,
    0x00, 0x00, 0x08, 0x00, 0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x02, 0x00, 0x00, 0x00, 0x04, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x03, 0x80, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x60, 0x30, 0x00, 0x00, 0x00,
    0x00, 0x10, 0x60, 0x00, 0x00, 0x00, 0x00, 0x08, 0x40, 0x00, 0x00, 0x00, 0x00, 0x04, 0x80, 0x00,
    0x00, 0x00, 0x00, 0x04, 0x80, 0x00, 0x00, 0x00, 0x00, 0x04, 0x80, 0x00, 0x00, 0x00, 0x00, 0x02,
    0x80, 0x00, 0x00, 0x00, 0x00, 0x02, 0x80, 0x00, 0x00, 0x00, 0x00, 0x02, 0x80, 0x00, 0x00, 0x00,
    0x00, 0x04, 0x80, 0x00, 0x00, 0x00, 0x00, 0x04, 0x40, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x20, 0x00,
    0x00, 0x00, 0x00, 0x08, 0x18, 0x00, 0x00, 0x00, 0x00, 0x30, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xe0};
// 'rain', 48x32px
const unsigned char rain[] PROGMEM = {
    0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x03, 0x81, 0x80, 0x00, 0x00, 0x00, 0x06, 0x00, 0x60,
    0x00, 0x00, 0x00, 0x08, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x10, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x30,
    0x00, 0x00, 0x30, 0x00, 0x00, 0x20, 0x00, 0x00, 0x18, 0x00, 0x00, 0x20, 0x00, 0x00, 0x08, 0x00,
    0x00, 0x20, 0x00, 0x00, 0x04, 0x00, 0x00, 0x40, 0x00, 0x00, 0x07, 0x80, 0x00, 0xc0, 0x00, 0x00,
    0x00, 0xc0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x20, 0x02, 0x00, 0x00, 0x00, 0x00, 0x10, 0x04, 0x00,
    0x00, 0x00, 0x00, 0x18, 0x04, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x08, 0x00, 0x00, 0x00, 0x00, 0x08, 0x04, 0x00, 0x00, 0x00, 0x00, 0x08, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x08, 0x04, 0x00, 0x00, 0x00, 0x00, 0x10, 0x02, 0x00, 0x00, 0x00, 0x00, 0x30, 0x01, 0x80,
    0x00, 0x00, 0x00, 0x60, 0x00, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x21, 0x08, 0x42, 0x10, 0x00, 0x00, 0x42, 0x10, 0x84, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x10, 0x84, 0x21, 0x00, 0x00, 0x04, 0x21,
    0x08, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x84, 0x21, 0x08, 0x00, 0x00};

// 'sunny', 48x32px
const unsigned char sunny[] PROGMEM = {
    0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x41, 0x08, 0x00, 0x00, 0x00, 0x00, 0x21, 0x08, 0x00, 0x00, 0x00, 0x18,
    0x20, 0x10, 0x60, 0x00, 0x00, 0x0c, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x06, 0x00, 0x01, 0x80, 0x00,
    0x00, 0x02, 0x0f, 0xc1, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x0c,
    0x00, 0x00, 0x00, 0x30, 0x80, 0x04, 0x30, 0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01,
    0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00,
    0x03, 0xf2, 0x00, 0x01, 0x1f, 0x00, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x30,
    0x80, 0x04, 0x30, 0x00, 0x00, 0x00, 0xc0, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00,
    0x00, 0x02, 0x0f, 0xc1, 0x00, 0x00, 0x00, 0x06, 0x00, 0x01, 0x80, 0x00, 0x00, 0x0c, 0x00, 0x00,
    0xc0, 0x00, 0x00, 0x18, 0x20, 0x10, 0x60, 0x00, 0x00, 0x00, 0x21, 0x08, 0x00, 0x00, 0x00, 0x00,
    0x41, 0x08, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00};

// 'water_droplet', 16x23px
const unsigned char water_droplet [] PROGMEM = {
    0xff, 0x7f, 0xfe, 0x3f, 0xfe, 0x3f, 0xfc, 0xbf, 0xf1, 0x9f, 0xe3, 0xcf, 0xef, 0xe7, 0xcf, 0xe7, 
    0x9f, 0xf3, 0x9f, 0xfb, 0x3f, 0xf9, 0x3f, 0xf9, 0x7f, 0xfd, 0x7f, 0xfc, 0x7f, 0xfc, 0x7f, 0xe4, 
    0x7f, 0xe4, 0x3f, 0xcd, 0x3f, 0x09, 0x9f, 0x33, 0xcf, 0xe3, 0xe0, 0x0f, 0xfe, 0x7f
};

// 'wind_gust', 28x23px
const unsigned char wind_gust [] PROGMEM = {
    0xff, 0xc0, 0xff, 0xf0, 0xff, 0xc0, 0xff, 0xf0, 0xff, 0xc0, 0x7f, 0xf0, 0xff, 0xfc, 0x7c, 0x70, 
    0xff, 0xf0, 0x70, 0x10, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x80, 0x07, 0xff, 0x80, 
    0xff, 0xff, 0xff, 0x80, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 
    0x80, 0x00, 0x00, 0xf0, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x1f, 0xf0, 
    0x00, 0x00, 0x0f, 0xf0, 0x80, 0x00, 0x0f, 0xf0, 0xff, 0xff, 0x87, 0xf0, 0xff, 0xfc, 0x0f, 0xf0, 
    0xff, 0xfc, 0x0f, 0xf0, 0xff, 0xfc, 0x1f, 0xf0, 0xff, 0xff, 0x7f, 0xf0
};