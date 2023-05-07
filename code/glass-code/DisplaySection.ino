void DisplayInit()
{
    // display.ssd1306_command(0xA0);
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    { // Address 0x3D for 128x64
        Serial.println(F("SSD1306 allocation failed"));
        for (;;);
    }
    // delay(1000);
    display.ssd1306_command(0xA0);


    // START
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(20,15);
    display.print("WELCOME");
    display.setCursor(20,30);
    display.print("WELCOME");
    display.setCursor(20,45);
    display.print("WELCOME");
    display.display(); 
    // while(1);
    // END
}

void DataProcessing(String data) 
{
    int dataLength = data.length();
    
    String firstLine  ="";
    String secondLine ="";
    String thirdLine  ="";

    int dataCounter=0;

    // used to clear array START
    for (int i=0; i<3;i++) {
        lines[i]="";
    }
    // used to clear array END

    for (int i = 0; i < dataLength; i++)
    {
        if(data[i]==':') 
        {
            dataCounter++;
            continue;
        }
        lines[dataCounter]+=data[i];
    }
// ines[0] = '*'
// ines[1] = 'sree1'
// ines[2] = 'sree2'

    Serial.println(lines[0]);
    Serial.println(lines[1]);
    Serial.println(lines[2]);
}

void ShowOnDisplay(String data1,String data2,String data3)
{
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(20,15);
    display.print(data1);
    display.setCursor(20,30);
    display.print(dataShorter(data3));
    display.setCursor(20,45);
    display.print(data3);
    display.display(); 
}

String dataShorter(String toShort)
{
    String dOut=toShort;
    int length = toShort.length();
    int MAX_LENGTH=10;
    if(length>MAX_LENGTH)
    {
        dOut=toShort.substring( length - MAX_LENGTH);
        Serial.println(dOut);
    }
    return dOut;
}
