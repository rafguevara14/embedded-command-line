// #pragma once
// #include <stdint.h>
// #include <stddef.h>



// namespace hardware{

// 	constexpr float TIMER_PERIOD_MS(float prescale) {
// 		return 1000.0*(255.0*prescale)/F_CPU;
// 	}

// 	using vregister = uint8_t volatile;
// 	using isr_handler = void(*)();

// 	namespace gpio{
// 		enum pin { zero, one, two, three, four, five, six, seven };
// 		enum port { B, C, D };
// 		enum direction { IN, OUT };
// 		enum resistor { FLOATING, PULLUP };
// 	}
// 	namespace uart{

// 		constexpr vregister uart0 = 

// 		union uUCSRA{
// 			struct {
// 				vregister MPCMn  : 1;
// 				vregister U2Xn  : 1;
// 				vregister UPEn  : 1;
// 				vregister DORn  : 1;
// 				vregister FEn  : 1;
// 				vregister UDREn  : 1;
// 				vregister TXCn  : 1;
// 				vregister RXCn  : 1;
// 			};

// 			vregister port;
// 		};
// 		union uUCSRB{
// 			struct {
// 				vregister TXB8n : 1;
// 				vregister RXB8n : 1;
// 				vregister UCSZn2 : 1;
// 				vregister TXENn : 1;
// 				vregister RXENn : 1;
// 				vregister UDRIEn : 1;
// 				vregister TXCIEn : 1;
// 				vregister RXCIEn : 1;
// 			};

// 			vregister port;
// 		};
// 		union uUCSRC{
// 			struct {
// 				vregister UCPOLn : 1;
// 				vregister UCSZn : 2;
// 				vregister USBSn : 1;
// 				vregister UPMn : 2;
// 				vregister UMSELn : 2;
// 			};

// 			vregister port;
// 		};

// 	}; // uart namespace

// 	namespace timer {

// 		union TIMSK{
// 			struct{
// 				vregister TOIE  : 1;
// 				vregister OCIEA : 1;
// 				vregister OCIEB : 1;
// 				vregister RESERVED : 5;
// 			};
// 			vregister port;
// 		};


// 		union TIFR{
// 			struct{
// 				vregister TOV  : 1;
// 				vregister OCFA : 1;
// 				vregister OCFB : 1;
// 				vregister RESERVED : 5;
// 			};
// 			vregister port;
// 		};

// 		union TCCRnA{
// 			struct{
// 				vregister WGM : 2;
// 				vregister RESERVED : 2;
// 				vregister COMB : 2;
// 				vregister COMA : 2;
// 			};
// 			vregister port;
// 		};

// 		union TCCRnB{
// 			struct{
// 				vregister CS2 : 3;
// 				vregister WGM2 : 1;
// 				vregister RESERVED : 2;
// 				vregister FOCB : 1;
// 				vregister FOCA : 1;
// 			};
// 			vregister port;
// 		};

// 	}; // timer namespace

// }; // register namespace