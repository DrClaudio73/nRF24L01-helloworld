/*
 * 1. Open up the project properties
 * 2. Visit C/C++ General > Preprocessor Include Paths, Macros, etc
 * 3. Select the Providers tab
 * 4. Check the box for "CDT GCC Built-in Compiler Settings"
 * 5. Set the compiler spec command to "xtensa-esp32-elf-gcc ${FLAGS} -E -P -v -dD "${INPUTS}""
 * 6. Rebuild the index
*/

#include <esp_log.h>
#include <string>
#include "sdkconfig.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "driver/gpio.h"
#include <RF24.h>

#include "sdkconfig.h"

static char tag[] = "test_nrf24";

extern "C" {
    void task_test_nrf24(void);
}



void task_test_nrf24(void) {
        char pino[50];
        int level=0;

    RF24 rf24(25,15); //ce , csn
    //rf24.printDetails();
    rf24.begin();
    rf24.setPALevel(RF24_PA_HIGH);
    rf24.setChannel(0x4c);
    rf24.setCRCLength(RF24_CRC_8);
    rf24.setDataRate(RF24_2MBPS);
    rf24.setAddressWidth(5);
    rf24.setRetries(5,15);
    rf24.enableDynamicPayloads();
    uint8_t txAddress[5] = {0x11, 0x22, 0x33, 0x44, 0x55};
    rf24.openWritingPipe(txAddress);
    while (true){
        rf24.write("Ciao Claudio te lo sei meritato", 32);
        ESP_LOGD(tag, "Transmitted data");
        sprintf(pino,"Che bello. %d",level);
        level=1-level;
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        rf24.write(pino, 32);
        rf24.printDetails();
        ESP_LOGD(tag, "Transmitted data");
        ESP_LOGD(tag, "test done");
    }
    vTaskDelete(NULL);
}

/*static char tag2[]="cpp_helloworld";

extern "C" {
	void app_main(void);
}

class Greeting {
public:
	void helloEnglish() {
		ESP_LOGD(tag2, "Hello %s", name.c_str());
	}

	void helloFrench() {
		ESP_LOGD(tag2, "Bonjour %s", name.c_str());
	}

	void setName(std::string name) {
		this->name = name;
	}
private:
	std::string name = "";

};

void app_main(void)
{
	Greeting myGreeting;
	myGreeting.setName("Neil");
    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);
    int level = 0;
    while(true){
        myGreeting.helloEnglish();
        myGreeting.helloFrench();
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        gpio_set_level(GPIO_NUM_2, level);
        level = !level;
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        task_test_nrf24();
        //printf("ueh     ");
        //cout<<"ciao";
        //int* ignore=&level;
        //task_test_nrf24((void*) ignore);
        //ESP_LOGI(tag,"ciao\n");
    }
}
*/

extern "C" {
	void app_main(void);
}

void app_main(void)
{
 
    task_test_nrf24();
   
}
