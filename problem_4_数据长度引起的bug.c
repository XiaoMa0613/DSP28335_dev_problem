
/*下面的这段代码是22L中检测错误的函数，逐位检查是否为1，为1就记录下位置，返回的是错误的位置和个数
输入的num为64位，这没有问题，哪怕DSP是32位的*/
uint8_t* Check_Err_bits(uint64_t num, uint8_t* size)
{
	uint8_t positions[40];
	uint8_t count = 0;
	for (int i = 0; i < 40; i++) {
		if (num & (1ULL << i)) {   //问题出在这里，在32位的DSP上1默认是int，也就是32位
		//确保1时64位的，在1后面添加ULL（Unsigned Long Long），不然会引起不可预料的bug
			positions[count] = i;
			count++;
		}
	}
	uint8_t* result = (uint8_t*)malloc(count * sizeof(uint8_t));
	for (int i = 0; i < count; i++) {
		result[i] = positions[i];
	}
	*size = count;
	return result;
}

/*函数在32位系统上运行时会遇到问题，原因在于1 << i这个操作。
在C语言中，整数常量1默认是int类型，而在32位系统中，int通常是32位的。
当i的值达到或超过32时，1 << i操作的行为是未定义的（Undefined Behavior）。
这意味着，当i等于32时，你期望的是将1左移32位，但实际上这个操作可能不会按预期工作，导致函数逻辑出错。*/



/*上面的函数运用*/
if(SystemError.all & (~Last_Err)) //结果为真，表示有新增错误，为假表示错误减少或不变，则不记录
{
	result = Check_Err_bits(SystemError.all & (~Last_Err), &size);//查找新错误
	for(uint8_t i = 0; i < size; i++)
	{
		if(Errcode_To[result[i]] != 0X00) //0X00为Errcode_To错误映射表中的占空位，映射表的元素顺序与错误结构体一样，其元素值与映射表相同
			Record_SetEvent(Screen_Alarm, 22, Errcode_To[result[i]], 0); //记录新错误
	}
}
Last_Err = SystemError.all;