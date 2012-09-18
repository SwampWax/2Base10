intu convertToDecimal(char* conversionValue,intu sourceBase)
{
	/** it will be easier for us to calculate the decimal
	  value of the new string if we first create a new
	  string which contains those values in reverse,
	  and while we're at it we will uppercase any letter
	  values in the original string */
	intu valueLength = strlen(conversionValue);
	char* reverseValue = new char[valueLength];
	for (int i = 1; i <= valueLength; ++i)
	{
		char swapChar = conversionValue[valueLength-i];
		if (swapChar >= 97 /*a*/ || swapChar <= 122 /*z*/)
		{
			swapChar-=32; // make it uppercase
		}
		else if (!(swapChar >= 48) && !(swapChar <= 57))
		{
			fprintf(stderr,"Character %d is not a valid number!",(valueLength-i));
			exit(ERR_INVALIDCHAR);
		}
		else if (swapChar == 0)
		{
			fprintf(stderr,"You hit a sandbar and it destroyed your ship.");
			exit(ERR_INVALIDCHAR);
		}
		reverseValue[i-1] = swapChar;
	}

	/* Now that we've reversed our string and performed some
	  basic error checks, it's time to convert it into decimal */
	char scratchAnswer[500];
	char thisChar;

	bool useLetters = (sourceBase > 10) ? true : false;
	intu numberLimit = (sourceBase-1), letterLimit = 0;
	intu runningTotal = 0, counter = 0;

	if (numberLimit > 10)
	{	
		letterLimit = numberLimit - 10;
		numberLimit = 10;	
	}
	while (1)
	{
		thisChar = *reverseValue++; counter++;
		if (thisChar >= 65 /*A*/ && thisChar <= 90 /*Z*/)
		{
			thisChar -= 7;
		}
		else if (thisChar == 0)
		{
			break;
		}
		intu char2Num = thisChar - 48;
		if (char2Num >= sourceBase)
		{
			fprintf(stderr,"Digit %u is too big for the specified base %u!\n",char2Num,sourceBase);
			exit(ERR_OUTOFRANGE);
		}
		runningTotal += char2Num * pow(sourceBase,counter);
	}
	return runningTotal; 
}
