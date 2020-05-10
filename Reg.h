const int MAX_SYM{ 1024 };
class Reg
{
	static inline const std::map<QString, HKEY> mKeys{
		{"HKEY_CLASSES_ROOT", HKEY_CLASSES_ROOT },
		{"HKEY_CURRENT_USER", HKEY_CURRENT_USER },
		{"HKEY_LOCAL_MACHINE", HKEY_LOCAL_MACHINE },
		{"HKEY_USERS", HKEY_USERS },
		{"HKEY_CURRENT_CONFIG", HKEY_CURRENT_CONFIG }
	};
	QString mParam;
	HKEY mKey;
	QString mBush;
	QSettings mReg;
	size_t mSizeBuffer;
	std::vector<u8> mData;
public:
	explicit Reg(const QString& path, const size_t& sz_data = MAX_SYM);
	~Reg();
	Reg(const Reg& d) = delete;
	Reg(Reg&& d) = delete;

	QStringList childGroups()const;
	QStringList allKeys()const;

	QString getBush();
	QString getParam();

	Reg& value(const QString& param = nullptr);

	QString toString()const;
	QString toHex()const;
	u64 toU64()const;
};