#ifndef MYSTRING_H_INCLUDED
#define MYSTRING_H_INCLUDED
class MyString
{
public:
		MyString(char string[]);

		~MyString();

		MyString(const MyString&);

		friend ostream& operator<<(ostream &, const MyString &);
		

		MyString& operator+=(const MyString&);

		
	

public:
	char *string_point;
	unsigned int string_length;


};

MyString::MyString(char string[])
{
	int i = 0;
	char *p = string;
	while (*(p+i)!='\0')
	{
		
		cout << *(p + i) << endl;
		i++;
	}
	string_length = i + 1;
	string_point = new char[string_length];//不加1准备玩蛋吧！

	for (i = 0; *(p + i) != '\0';i++)
	{
		*(string_point + i) = *(p + i);
	}
	*(string_point + i) = '\0';

	
};

MyString::~MyString()
{
	delete [] string_point ;
	
};
MyString::MyString(const MyString& old_string)
{
	int i = 0;
	char *p = old_string.string_point;
	while (*(p + i) != '\0')
	{
		i++;
	}

	string_length = i + 1;
	string_point = new char[string_length];

	for (i = 0; *(p + i) != '\0'; i++)
	{
		*(string_point + i) = *(p + i);
	}
	*(string_point + i) = '\0';
	
	
};
ostream& operator<<(ostream &os, const MyString &my_string)
{
	cout << "该字符串为："<<my_string.string_point << endl;
	return os;
}
MyString& MyString::operator+=(const MyString& old_string)
{
	int all_length=old_string.string_length+string_length;
	int i = 0, j = 0;
	MyString tmp = old_string;

	delete[] string_point;

	string_point = new char[all_length - 1];
	string_length = all_length - 1;
	while (*(tmp.string_point+i)!='\0')
	{
		*(string_point + j) = *(tmp.string_point + i);
		i++; j++;
	}
	i = 0;
	while (*(old_string.string_point + i) != '\0')
	{
		*(string_point + j) = *(tmp.string_point + i);
		i++; j++;
	}
	*(string_point + j) = '\0';

	return *this;
		

}


#endif // MYSTRING_H_INCLUDED