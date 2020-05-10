#include <Header.h>
#include "Reg.h"
Reg::Reg(const QString& path, const size_t& sz_data) :
	mParam{ path },
	mKey{ mKeys.at(mParam.replace('/', '\\').split("\\")[0]) },
	mBush{ mParam.mid(mParam.replace('/', '\\').indexOf("\\") + 1) },
	mReg{ path, QSettings::NativeFormat },
	mSizeBuffer{ sz_data }
{
	mData.reserve(mSizeBuffer);
}

Reg::~Reg()
{
	RegCloseKey(mKey);
}

QStringList Reg::childGroups()const
{
	return mReg.childGroups();
}

QStringList Reg::allKeys()const
{
	return mReg.allKeys();
}

QString Reg::getBush()
{
	return mBush;
}

QString Reg::getParam()
{
	return mParam;
}

Reg& Reg::value(const QString& param)
{
	mData.clear();
	mData.resize(mSizeBuffer);
	DWORD retSize;
	DWORD dwType;
	HKEY key;
	auto i{ param.indexOf('\\') };
	QString formatBush =
		param.indexOf('\\') != -1 ?
		(mBush + "\\" + param.mid(0, param.lastIndexOf('\\'))) : mBush;

	::RegOpenKeyEx(
		mKey,
		formatBush.toStdWString().c_str(),
		0, KEY_READ | KEY_WOW64_64KEY, &key);

	QString formatParam = param.mid(param.lastIndexOf('\\') + 1);
	::RegQueryValueEx(
		key,
		formatParam.toStdWString().c_str(),
		0,
		&dwType,
		mData.data(),
		&retSize);
	retSize = retSize < mSizeBuffer ? retSize : 0;
	mData.resize(retSize);
	RegCloseKey(mKey);

	return *this;
}

QString Reg::toString() const
{
	QString out;
	int i{ 0 };
	for (const auto& elm : mData)
	{
		if (i++ % 2 == 0)
		{
			out += elm;
		}
	}
	return out;
}

QString Reg::toHex() const
{
	QString out;
	for (const auto& elm : mData)
	{
		out += QString::number(elm, 16);
	}
	return out;

}

u64 Reg::toU64() const
{
	u64 out{ 0 };
	int idx{ 0 };
	for (const auto& elm : mData)
	{
		out |= (static_cast<u64>(elm) & 0xFF) << idx;
		idx += 8;
	}
	return out;
}
