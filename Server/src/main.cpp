#include "soci.h"
#include "odbc/soci-odbc.h"
#include <iostream>
#include <string>
#include <exception>

using namespace soci;
using namespace std;

bool get_name(string &name)
{
	cout << "Enter name: ";
	cin >> name;
	if (!cin)
		return false;
	return true;
}

int main()
{
	try
	{
		session sql(odbc,"");

		int count;
		sql << "select count(*) from nhanvien", into(count);

		cout << "We have " << count << " employees.\n";

		string name;
		while (get_name(name))
		{
			string employID;
			indicator ind;
			sql << "select manv from nhanvien where tennv = :name",
				into(employID, ind), use(name);

			if (ind == i_ok)
			{
				cout << "The employee ID number is " << employID << '\n';
			}
		}
	}
	catch (exception const &e)
	{
		cerr << "Error: " << e.what() << '\n';
	}
}