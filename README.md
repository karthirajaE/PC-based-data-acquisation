# PC-based-data-acquisation
# components:
      AT89C51 microcontroller
      DS1307 RTC(real time clock)
      MPC3204 ADC(analog to digital convertor)
      LM35 temperature sensor
      16x2 alpha numeric LCD display
      PC/laptop
      
 # interfacing:
      AT89C51  --I2C--> DS1307(RTC)
         ,,    --SPI--> MPC3204(ADC) --cable-->LM35 temp sensor
         ,,    --UART--> PC/laptop
         ,,    --cable--> LCD
 # In main:
       step 1 --> initialize UART, LCD
       step 2 -->read data from RTC by using I2C protocol and display it in both LCD and PC(using UART)
       step 3 -->read data from ADC by using SPI protocol and display it in both LCD and PC(using UART)
       step 4 -->reinitialize the LCD
       step 5 -->repeat step 2 to 4 inifinitely
