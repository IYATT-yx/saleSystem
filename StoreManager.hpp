#pragma once
extern "C"
{
	#include "sqlite3.h"
}

#include <vector>

typedef struct
{
	int id;
	CString name;
	double price;
	int stock;
}productStruct;

typedef struct
{
    CString username;
	CString password;
}loginInfoStruct;

typedef std::vector<productStruct> productsVector;

class StoreManager
{
private:
	static sqlite3* db;
	static productStruct product;
	static loginInfoStruct loginInfo;

private:
	static int readLoginInfoCallback(void* data, int argc, char** argv, char** colName);

	/**
	 * @brief UTF-8 编码窄字符串转 GBK 编码 CString
	 * @param utf8Str 
	 * @return 
	 */
	static CString utf8ToGbk(const char* utf8Str);

	/**
	 * @brief GBK 编码 CString 转 UTF-8 窄字符串
	 * @param gbkStr 
	 * @return 
	 */
	static char* gbkToUtf8(const CString& gbkStr);

public:
	/**
	 * @brief 连接数据库
	 * @param databasePath 数据库文件路径
	 */
	static void connect(CString& databasePath);

	/**
	 * @brief 读取登录信息
	 * @param username 用户名
	 * @param password 密码
	 */
	static void readLogin(CString& username, CString& password);

	/**
	 * @brief 修改密码
	 * @param username 要修改密码的用户 
	 * @param password 新密码
	 */
	static bool writePassword(CString& username, CString& password);

	/**
	 * @brief 关闭数据库
	 */
	static void close();

	/**
	 * @brief 读取商品信息
	 * @param products 商品信息数组
	 */
	static void readProducts(productsVector& products);

	/**
	 * @brief 写入商品信息
	 * @param products 商品信息数据
	 */
	static void writeProducts(productsVector& products);

	/**
	 * @brief 修改商品信息
	 * @param products 
	 */
	static void modifyProducts(productsVector& products);
};

