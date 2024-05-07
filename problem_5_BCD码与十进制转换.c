/* BCD码，全称为Binary-Coded Decimal，中文名为二进制编码的十进制数，
是一种用二进制编码表示的十进制数。在计算机中，BCD码常常被用来表示和处理十进制数，
因为二进制数在计算机中的运算更加方便.*/

int bcdToDecimal(int bcdValue) {
    int decimalValue = 0;

    // 将BCD码转换为十进制数
    decimalValue = ((bcdValue & 0xF0) >> 4) * 10 + (bcdValue & 0x0F);

    return decimalValue;
}

int decimalToBcd(int decimalValue) {
    int bcdValue = 0;

    // 将十进制数转换为BCD码
    bcdValue = ((decimalValue / 10) << 4) | (decimalValue % 10);

    return bcdValue;
}