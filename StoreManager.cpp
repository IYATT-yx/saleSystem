#include "pch.h"
#include "StoreManager.hpp"

#include <string>
#include <stdexcept>

sqlite3* StoreManager::db = nullptr;
loginInfoStruct StoreManager::loginInfo;
productStruct StoreManager::product;

void StoreManager::connect(CString& databasePath)
{
	if (StoreManager::db != nullptr)
	{
		return;
	}

	CW2A databasePathA(databasePath.GetString()); // 宽字符串转普通字符串
	if (sqlite3_open(databasePathA, &StoreManager::db) != SQLITE_OK)
	{
		std::string error = "打开数据库失败：" + std::string(sqlite3_errmsg(StoreManager::db));
		throw std::runtime_error(error);
	}
}

void StoreManager::close()
{
	if (StoreManager::db != nullptr)
	{
		sqlite3_free(StoreManager::db);
		StoreManager::db = nullptr;
	}
}

int StoreManager::readLoginInfoCallback(void* data, int argc, char** argv, char** colName)
{
	(void)data;
	(void)argc;
	(void)colName;
	StoreManager::loginInfo.username = argv[1];
	StoreManager::loginInfo.password = argv[2];
	return 0;
}

void StoreManager::readLogin(CString& username, CString& password)
{
	if (StoreManager::db == nullptr)
	{
		std::string error = "请连接数据库后再读取登录信息";
		throw std::runtime_error(error);
	}

	const char* sqlA = "select * from users";
	char* errorA = nullptr;
	if (sqlite3_exec(StoreManager::db, sqlA, StoreManager::readLoginInfoCallback, nullptr, &errorA) != SQLITE_OK)
	{
		std::string error = "读取登录信息失败：" + std::string(errorA);
		sqlite3_free(errorA);
		throw std::runtime_error(error);
	}

	username = StoreManager::loginInfo.username;
    password = StoreManager::loginInfo.password;
}

bool StoreManager::writePassword(CString& username, CString& password)
{
	if (StoreManager::db == nullptr)
	{
		std::string error = "请连接数据库后再读取登录信息";
		throw std::runtime_error(error);
	}

	CString sql;
	sql.Format(L"update users set password = '%s' where username = '%s'", password.GetString(), username.GetString());
	CW2A sqlA(sql);
	char* errorA = nullptr;
	if (sqlite3_exec(StoreManager::db, sqlA, nullptr, nullptr, &errorA) != SQLITE_OK)
	{
		CA2W errorW(errorA);
		AfxMessageBox(errorW);
		sqlite3_free(errorA);
		return false;
	}
	return true;
}

CString StoreManager::utf8ToGbk(const char* utf8Str)
{
	int wideCharLen = MultiByteToWideChar(CP_UTF8, 0, utf8Str, -1, nullptr, 0);
	if (wideCharLen <= 0)
	{
		return CString();
	}

	wchar_t* wideCharStr = new wchar_t[wideCharLen];
	MultiByteToWideChar(CP_UTF8, 0, utf8Str, -1, wideCharStr, wideCharLen);

	int gbkLen = WideCharToMultiByte(CP_ACP, 0, wideCharStr, -1, nullptr, 0, nullptr, nullptr);
	if (gbkLen <= 0)
	{
		delete[] wideCharStr;
		return CString();
	}

	char* gbkStr = new char[gbkLen];
	WideCharToMultiByte(CP_ACP, 0, wideCharStr, -1, gbkStr, gbkLen, nullptr, nullptr);

	CString result(gbkStr);

	delete[] wideCharStr;
	delete[] gbkStr;

	return result;
}

char* StoreManager::gbkToUtf8(const CString& gbkStr)
{
	// 获取宽字符字符串的长度
	int wideCharLen = gbkStr.GetLength();
	if (wideCharLen <= 0)
	{
		return nullptr; // 如果字符串为空，直接返回 nullptr
	}

	// 将 CString 转换为宽字符数组
	const WCHAR* gbkW = gbkStr.GetString();

	// 获取需要的 UTF-8 编码字符串的长度（包括结尾的 '\0'）
	int utf8Len = WideCharToMultiByte(CP_UTF8, 0, gbkW, -1, nullptr, 0, nullptr, nullptr);
	if (utf8Len <= 0)
	{
		return nullptr; // 如果转换失败，返回 nullptr
	}

	// 分配内存用于存储 UTF-8 编码的字符串
	char* utf8Str = new char[utf8Len];

	// 执行转换
	if (WideCharToMultiByte(CP_UTF8, 0, gbkW, -1, utf8Str, utf8Len, nullptr, nullptr) == 0)
	{
		delete[] utf8Str; // 如果转换失败，释放已分配的内存
		return nullptr;
	}

	return utf8Str; // 返回转换后的 UTF-8 字符串
}


void StoreManager::readProducts(productsVector& products)
{
	if (StoreManager::db == nullptr)
	{
		std::string error = "请连接数据库后再读取商品信息";
		throw std::runtime_error(error);
	}

	products.clear();
	
	const char* sqlA = "select * from products";
	char** result = nullptr;
	char* errorA = nullptr;
	int rows, cols;
	if (sqlite3_get_table(StoreManager::db, sqlA, &result, &rows, &cols, &errorA) != SQLITE_OK)
	{
		CA2W errorW(errorA);
		AfxMessageBox(errorW);
		sqlite3_free(errorA);
		return;
	}

	productStruct product;
	for (int row = 1; row <= rows; ++row)
	{
		product.id = std::stoi(result[row * cols + 0]);
		product.name = StoreManager::utf8ToGbk(result[row * cols + 1]);
		product.price = std::stod(result[row * cols + 2]);
		product.stock = std::stoi(result[row * cols + 3]);
		products.push_back(product);
	}
}

void StoreManager::writeProducts(productsVector& products)
{
	if (StoreManager::db == nullptr)
	{
		std::string error = "请连接数据库后再写入商品信息";
		throw std::runtime_error(error);
	}

	CString sql;
	char* errorA = nullptr;
	for (productStruct product : products)
	{
		sql.Format(L"insert into products (name, price, stock) values ('%s', %f, %d)", product.name.GetString(), product.price, product.stock);
		char* sqlA = StoreManager::gbkToUtf8(sql);
		if (sqlite3_exec(StoreManager::db, sqlA, nullptr, nullptr, &errorA) != SQLITE_OK)
		{
			CA2W errorW(errorA);
			AfxMessageBox(errorW);
			sqlite3_free(errorA);
			delete[] sqlA;
			break;
		}
		else
		{
			delete[] sqlA;
		}
	}
}

void StoreManager::modifyProducts(productsVector& products)
{
	if (StoreManager::db == nullptr)
	{
		std::string error = "请连接数据库后再修改商品信息";
		throw std::runtime_error(error);
	}

	CString sql;
	char* errorA = nullptr;
	for (productStruct product : products)
	{
		sql.Format(L"update products set price = %f, stock = %d where name = '%s'", product.price, product.stock, product.name.GetString());
		char* sqlA = StoreManager::gbkToUtf8(sql);

		if (sqlite3_exec(StoreManager::db, sqlA, nullptr, nullptr, &errorA) != SQLITE_OK)
		{
			CA2W errorW(errorA);
			AfxMessageBox(errorW);
			sqlite3_free(errorA);
			delete[] sqlA;
			break;
		}
		else
		{
			delete[] sqlA;
		}
	}
}