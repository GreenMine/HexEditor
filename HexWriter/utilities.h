char to_table_format(char symbol) {
	if (symbol == 0x00)
		return '.';
	if (symbol == 0xA)
		return 'N';
	return symbol;
}