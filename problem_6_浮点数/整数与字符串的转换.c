void intToCharArray(int num, char *charArray)
{
    int i = 0;
    if (num == 0) {
        charArray[i++] = '0';
    } else {
        while (num != 0) {
            charArray[i++] = '0' + num % 10;
            num /= 10;
        }
    }

    // 反转字符串
    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = charArray[start];
        charArray[start] = charArray[end];
        charArray[end] = temp;
        start++;
        end--;
    }
}
void floatToCharArray(float num, char *charArray)
{
    int intPart = (int)num;
    float decimalPart = num - intPart;

    // 转换整数部分
    intToCharArray(intPart, charArray);

    // 找到小数点的位置
    int length = strlen((const char*)charArray);
    charArray[length++] = '.';

    // 转换小数部分
    decimalPart *= 100; // 保留小数点后2位
    if(decimalPart < 10) //避免出现0.09显示成0.9的bug
    	charArray[length++] = '0';
    intToCharArray((int)decimalPart, charArray + length);
}
/*适合小数点较多的，也可在设置小数位数参数*/
void s_floatToCharArray(float num, char *charArray)
{
    int intPart = (int)num;
    float decimalPart = num - intPart;

    // 转换整数部分
    intToCharArray(intPart, charArray);

    // 找到小数点的位置
    int length = strlen((const char*)charArray);
    charArray[length++] = '.';
    while(decimalPart * 10 < 1) //decimalPart不能为0
    {
    	decimalPart *= 10;
    	charArray[length++] = '0';
    }
    // 转换小数部分
    decimalPart *= 10;
    intToCharArray((int)decimalPart, charArray + length);
}

//字符串转浮点，库函数
float result = atof(char* array);