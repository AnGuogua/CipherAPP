#include "cipher.h"

long long totalblocks = 0;
QString encrypt(QString pt, QString key)
{
	//对字符串进行分块处理
	struct ciblock *cib = new ciblock;
	cib->next = nullptr;
	struct ciblock *first = cib;
	totalblocks = ceil(1.0 * pt.size() / blocksize) + 1;
	//生成填充用的null值
	const QString null_c = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	QString randomnull;

	QRandomGenerator rng;
	rng.seed(QDateTime::currentMSecsSinceEpoch());  // 使用当前时间作为种子

	for (int i = 0; i < blocksize; ++i) {
		int index = rng.bounded(null_c.length());
		randomnull.append(null_c.at(index));
	}
	for (int i = 0; i < totalblocks; i++)
	{
		cib->next = nullptr;
		cib->id = i;
		cib->pt = pt.mid(i * blocksize, blocksize);
		if ((i + 1) * blocksize >= pt.size())
		{
			int size = cib->pt.size();
			if (size != blocksize)
			{
				cib->pt = cib->pt + randomnull;
				cib->pt = cib->pt.left(blocksize);
			}
			cib->next = new ciblock;
			cib->next->pt = randomnull + QString::number(blocksize - size);
			cib->next->pt = cib->next->pt.right(blocksize);
			cib->next->next = nullptr;
			break;  // 如果已经到达末尾，则退出循环
		}
		cib->next = new ciblock;
		cib = cib->next;
	}

	//开始进行密钥计算
	std::string hash;
	std::string key_str = key.toStdString();
	CryptoPP::SHA3_224 sha3_224;
	CryptoPP::SHA3_256 sha3_256;
	CryptoPP::SHA3_384 sha3_384;
	CryptoPP::SHA3_512 sha3_512;
	CryptoPP::SHA224 sha2_224;
	CryptoPP::SHA256 sha2_256;
	CryptoPP::SHA384 sha2_384;
	CryptoPP::SHA512 sha2_512;
	CryptoPP::SHA1 sha1;
	CryptoPP::MD5 md5;
	CryptoPP::MD4 md4;	
	CryptoPP::BLAKE2b blake2;
	switch (ht)
	{
	case SHA3_224:
		CryptoPP::StringSource(key_str, true,
			new CryptoPP::HashFilter(sha3_224,
				new CryptoPP::HexEncoder(new CryptoPP::StringSink(hash), false)
			)
		);
		break;
	case SHA3_256:
		CryptoPP::StringSource(key_str, true,
			new CryptoPP::HashFilter(sha3_256,
				new CryptoPP::HexEncoder(new CryptoPP::StringSink(hash), false)
			)
		);
		break;
	case SHA3_384:
		CryptoPP::StringSource(key_str, true,
			new CryptoPP::HashFilter(sha3_384,
				new CryptoPP::HexEncoder(new CryptoPP::StringSink(hash), false)
			)
		);
		break;
	case SHA3_512:
		CryptoPP::StringSource(key_str, true,
			new CryptoPP::HashFilter(sha3_512,
				new CryptoPP::HexEncoder(new CryptoPP::StringSink(hash), false)
			)
		);
		break;
	case SHA2_224:
		CryptoPP::StringSource(key_str, true,
			new CryptoPP::HashFilter(sha2_224,
				new CryptoPP::HexEncoder(new CryptoPP::StringSink(hash), false)
			)
		);
		break;
	case SHA2_256:
		CryptoPP::StringSource(key_str, true,
			new CryptoPP::HashFilter(sha2_256,
				new CryptoPP::HexEncoder(new CryptoPP::StringSink(hash), false)
			)
		);
		break;
	case SHA2_384:
		CryptoPP::StringSource(key_str, true,
			new CryptoPP::HashFilter(sha2_384,
				new CryptoPP::HexEncoder(new CryptoPP::StringSink(hash), false)
			)
		);
		break;
	case SHA2_512:
		CryptoPP::StringSource(key_str, true,
			new CryptoPP::HashFilter(sha2_512,
				new CryptoPP::HexEncoder(new CryptoPP::StringSink(hash), false)
			)
		);
		break;
	case SHA1:
		CryptoPP::StringSource(key_str, true,
			new CryptoPP::HashFilter(sha1,
				new CryptoPP::HexEncoder(new CryptoPP::StringSink(hash), false)
			)
		);
		break;
	case MD5:
		CryptoPP::StringSource(key_str, true,
			new CryptoPP::HashFilter(md5,
				new CryptoPP::HexEncoder(new CryptoPP::StringSink(hash), false)
			)
		);
		break;
	case MD4:
		CryptoPP::StringSource(key_str, true,
			new CryptoPP::HashFilter(md4,
				new CryptoPP::HexEncoder(new CryptoPP::StringSink(hash), false)
			)
		);
		break;
	case BLAKE2:
		CryptoPP::StringSource(key_str, true,
			new CryptoPP::HashFilter(blake2,
				new CryptoPP::HexEncoder(new CryptoPP::StringSink(hash), false)
			)
		);
		break;
	}
	
	unsigned long long result = 0;
	for (char ch : hash)
	{
		result = (result * 16 + (ch >= '0' && ch <= '9' ? ch - '0' : ch - 'A' + 10)) % ULLONG_MAX;
	}
	//生成随机数
	std::mt19937 generator(result);  // 初始化随机数
	std::uniform_int_distribution<size_t> distribution(0, characters.size() - 1);

	// 生成随机字符串
	cib = first;
	for (int i = 1; i <= totalblocks; i++)
	{
		QString randomString;
		for (size_t j = 0; j < blocksize; j++)
		{
			randomString += characters[distribution(generator)];
		}
		cib->key = randomString;
		cib = cib->next;
	}
	//开始加密
	cib = first;
	for (int i = 1; i <= totalblocks; i++)
	{

		int type = 0;
		for (QChar ch : cib->key)
		{
			type += ch.unicode();
		}
		type %= 2;//生成一个“随机”的
		if (type == 0)
		{
			cib->ci = xor_(cib->pt, cib->key);//异或
		}
		if (type == 1)
		{
			cib->ci = xand_(cib->pt, cib->key);//异与
		}
		cib = cib->next;

	}
	//打乱重排
	first = mergeSort(first);
	//合并
	QString res;
	cib = first;
	for (int i = 1; i <= totalblocks; i++)
	{
		res += cib->ci;
		cib = cib->next;
	}
	if (skipBase64)
	{
		return res;
	}
	std::string encoded;
	CryptoPP::StringSource ss(res.toStdString(), true, new CryptoPP::Base64Encoder(new CryptoPP::StringSink(encoded)));
	return QString::fromStdString(encoded);
}
QString decrypt(QString ci, QString key)
{
	//解码Base64
	if (!skipBase64)
	{
		std::string decoded;
		CryptoPP::StringSource ss(ci.toStdString(), true, new CryptoPP::Base64Decoder(new CryptoPP::StringSink(decoded)));
		ci = QString::fromStdString(decoded);
	}
	
	if (ci.size() % blocksize != 0)
	{
		return "CipherText length doesn't match";
	}
	//声明变量
	struct ciblock *cib = new ciblock;
	struct ciblock *first = cib;
	cib->next = nullptr;

	//开始进行密钥计算
	std::string hash;
	std::string key_str = key.toStdString();
	CryptoPP::SHA3_224 sha3_224;
	CryptoPP::SHA3_256 sha3_256;
	CryptoPP::SHA3_384 sha3_384;
	CryptoPP::SHA3_512 sha3_512;
	CryptoPP::SHA224 sha2_224;
	CryptoPP::SHA256 sha2_256;
	CryptoPP::SHA384 sha2_384;
	CryptoPP::SHA512 sha2_512;
	CryptoPP::SHA1 sha1;
	CryptoPP::MD5 md5;
	CryptoPP::MD4 md4;
	CryptoPP::BLAKE2b blake2;
	switch (ht)
	{
	case SHA3_224:
		CryptoPP::StringSource(key_str, true,
			new CryptoPP::HashFilter(sha3_224,
				new CryptoPP::HexEncoder(new CryptoPP::StringSink(hash), false)
			)
		);
		break;
	case SHA3_256:
		CryptoPP::StringSource(key_str, true,
			new CryptoPP::HashFilter(sha3_256,
				new CryptoPP::HexEncoder(new CryptoPP::StringSink(hash), false)
			)
		);
		break;
	case SHA3_384:
		CryptoPP::StringSource(key_str, true,
			new CryptoPP::HashFilter(sha3_384,
				new CryptoPP::HexEncoder(new CryptoPP::StringSink(hash), false)
			)
		);
		break;
	case SHA3_512:
		CryptoPP::StringSource(key_str, true,
			new CryptoPP::HashFilter(sha3_512,
				new CryptoPP::HexEncoder(new CryptoPP::StringSink(hash), false)
			)
		);
		break;
	case SHA2_224:
		CryptoPP::StringSource(key_str, true,
			new CryptoPP::HashFilter(sha2_224,
				new CryptoPP::HexEncoder(new CryptoPP::StringSink(hash), false)
			)
		);
		break;
	case SHA2_256:
		CryptoPP::StringSource(key_str, true,
			new CryptoPP::HashFilter(sha2_256,
				new CryptoPP::HexEncoder(new CryptoPP::StringSink(hash), false)
			)
		);
		break;
	case SHA2_384:
		CryptoPP::StringSource(key_str, true,
			new CryptoPP::HashFilter(sha2_384,
				new CryptoPP::HexEncoder(new CryptoPP::StringSink(hash), false)
			)
		);
		break;
	case SHA2_512:
		CryptoPP::StringSource(key_str, true,
			new CryptoPP::HashFilter(sha2_512,
				new CryptoPP::HexEncoder(new CryptoPP::StringSink(hash), false)
			)
		);
		break;
	case SHA1:
		CryptoPP::StringSource(key_str, true,
			new CryptoPP::HashFilter(sha1,
				new CryptoPP::HexEncoder(new CryptoPP::StringSink(hash), false)
			)
		);
		break;
	case MD5:
		CryptoPP::StringSource(key_str, true,
			new CryptoPP::HashFilter(md5,
				new CryptoPP::HexEncoder(new CryptoPP::StringSink(hash), false)
			)
		);
		break;
	case MD4:
		CryptoPP::StringSource(key_str, true,
			new CryptoPP::HashFilter(md4,
				new CryptoPP::HexEncoder(new CryptoPP::StringSink(hash), false)
			)
		);
		break;
	case BLAKE2:
		CryptoPP::StringSource(key_str, true,
			new CryptoPP::HashFilter(blake2,
				new CryptoPP::HexEncoder(new CryptoPP::StringSink(hash), false)
			)
		);
		break;
	}
	unsigned long long result = 0;
	for (char ch : hash)
	{
		result = (result * 16 + (ch >= '0' && ch <= '9' ? ch - '0' : ch - 'A' + 10)) % ULLONG_MAX;
	}

	//生成随机数
	std::mt19937 generator(result);  // 初始化随机数
	std::uniform_int_distribution<int> distribution(0, characters.size() - 1);
	totalblocks = ci.size() / blocksize;
	// 生成随机字符串
	for (int i = 1; i <= totalblocks; i++)
	{
		QString randomString;
		cib->id = i;
		cib->next = nullptr;
		for (int j = 0; j < blocksize; j++)
		{
			randomString += characters[distribution(generator)];
		}
		cib->key = randomString;
		if (i == totalblocks)
		{
			break;
		}
		cib->next = new ciblock;
		cib = cib->next;
	}
	//重排
	first = mergeSort(first);
	//将密码分块
	cib = first;
	for (int i = 0; i <= totalblocks; i++)
	{
		cib->ci = ci.mid(i * blocksize, blocksize);
		if ((i + 1) * blocksize >= ci.size())
		{
			break;  // 如果已经到达末尾，则退出循环
		}
		cib = cib->next;
	}
	//还原回原来的顺序
	first = mergeSort2(first);
	cib = first;
	for (int i = 1; i <= totalblocks; i++)
	{
		int type = 0;
		for (QChar ch : cib->key)
		{
			type += ch.unicode();
		}
		type %= 2;
		if (type == 0)
		{
			//解异或
			cib->pt = xor_(cib->ci, cib->key);
		}
		if (type == 1)
		{
			//解异或
			cib->pt = xand_(cib->ci, cib->key);
		}
		cib = cib->next;
	}
	//拼接
	QString res;
	cib = first;
	for (int i = 1; i <= totalblocks; i++)
	{
		res += cib->pt;
		cib = cib->next;
	}
	// 提取字符串的最后 blocksize 个字符
	QString substring = res.right(blocksize);

	// 遍历提取的子串，找到第一个数字字符的位置
	QString numberStr;
	for (int i = 0; i < substring.size(); ++i) {
		QChar ch = substring[i];
		if (ch.isDigit()) {
			numberStr.append(ch);
		}
	}

	// 将提取的数字字符串转换为整数
	bool ok;
	int nullsize = numberStr.toInt(&ok);
	if (!ok) {
		nullsize = 0; // 处理转换失败的情况
	}

	
	res = nullsize +"  "+res.left(res.size() - nullsize - blocksize);
	return res;
}
QString xor_(QString a, QString b)
{
	// 确保两个字符串的长度相同，按需调整
	size_t max_length = std::max(a.size(), b.size());
	QString extended_a = a;
	QString extended_b = b;

	// 扩展短的字符串以匹配最大长度
	extended_a.resize(max_length, '\0'); // 填充 '\0' 以扩展长度
	extended_b.resize(max_length, '\0'); // 填充 '\0' 以扩展长度

	QString result;
	result.resize(max_length);

	// 进行异或操作
	for (size_t i = 0; i < max_length; ++i)
	{
		result[i] = QChar(extended_a[i].unicode() ^ extended_b[i].unicode()); // 异或并存储结果
	}

	return result;
}

QString xand_(QString a, QString b)
{
	// 确保两个字符串的长度相同，按需调整
	size_t max_length = std::max(a.size(), b.size());
	QString extended_a = a;
	QString extended_b = b;

	// 扩展短的字符串以匹配最大长度
	extended_a.resize(max_length, '\0'); // 填充 '\0' 以扩展长度
	extended_b.resize(max_length, '\0'); // 填充 '\0' 以扩展长度

	QString result;
	result.resize(max_length);

	// 进行异与操作
	for (size_t i = 0; i < max_length; ++i)
	{
		std::bitset<8> bitset_a(extended_a[i].unicode());
		std::bitset<8> bitset_b(extended_b[i].unicode());
		std::bitset<8> bitresult;
		for (int j = 0; j < 8; j++)
		{
			if (bitset_a[j] == 0)
				bitresult[j] = 0;
			if (bitset_a[j] == 1)
				bitresult[j] = 1;
		}
		result[i] = QChar(static_cast<unsigned int>(bitresult.to_ulong()));
	}

	return result;
}
//对链表排序
ciblock *mergeSort(ciblock *head)
{
	// 基本情况：如果链表为空或只有一个节点，直接返回
	if (head == nullptr || head->next == nullptr)
	{
		return head;
	}

	// 找到链表的中间节点
	ciblock *slow = head;
	ciblock *fast = head;
	ciblock *prev = nullptr;

	while (fast != nullptr && fast->next != nullptr)
	{
		prev = slow;
		slow = slow->next;
		fast = fast->next->next;
	}

	// 在分割链表前，确保 prev 不为 nullptr
	if (prev != nullptr)
	{
		prev->next = nullptr;
	}

	// 递归地排序两半链表
	ciblock *l1 = mergeSort(head);
	ciblock *l2 = mergeSort(slow);

	// 合并排序好的链表
	return mergeTwoLists(l1, l2);
}

ciblock *mergeTwoLists(ciblock *l1, ciblock *l2)
{
	// 创建一个虚拟头节点来简化合并过程
	ciblock dummy;
	ciblock *tail = &dummy;

	// 合并两个链表
	while (l1 != nullptr && l2 != nullptr)
	{
		if (l1->key < l2->key)
		{
			tail->next = l1;
			l1 = l1->next;
		}
		else
		{
			tail->next = l2;
			l2 = l2->next;
		}
		tail = tail->next;
	}

	// 将剩余的部分添加到合并链表中
	if (l1 != nullptr)
	{
		tail->next = l1;
	}
	else
	{
		tail->next = l2;
	}

	return dummy.next;
}
ciblock *mergeSort2(ciblock *head)
{
	// 基本情况：如果链表为空或只有一个节点，直接返回
	if (head == nullptr || head->next == nullptr)
	{
		return head;
	}

	// 找到链表的中间节点
	ciblock *slow = head;
	ciblock *fast = head;
	ciblock *prev = nullptr;

	while (fast != nullptr && fast->next != nullptr)
	{
		prev = slow;
		slow = slow->next;
		fast = fast->next->next;
	}

	// 在分割链表前，确保 prev 不为 nullptr
	if (prev != nullptr)
	{
		prev->next = nullptr;
	}

	// 递归地排序两半链表
	ciblock *l1 = mergeSort2(head);
	ciblock *l2 = mergeSort2(slow);

	// 合并排序好的链表
	return mergeTwoLists2(l1, l2);
}

ciblock *mergeTwoLists2(ciblock *l1, ciblock *l2)
{
	// 创建一个虚拟头节点来简化合并过程
	ciblock dummy;
	ciblock *tail = &dummy;

	// 合并两个链表
	while (l1 != nullptr && l2 != nullptr)
	{
		if (l1->id < l2->id) {
			tail->next = l1;
			l1 = l1->next;
		}
		else {
			tail->next = l2;
			l2 = l2->next;
		}
		tail = tail->next;
	}

	// 将剩余的部分添加到合并链表中
	if (l1 != nullptr)
	{
		tail->next = l1;
	}
	else {
		tail->next = l2;
	}

	return dummy.next;
}