#ifndef USER
#define USER

class User{
private:
	std::string _name;
	std::string _secKey;

public:
	User(std::string pName, std::string pSecKey){
		_name = pName;
		_secKey = pSecKey;
	}

	bool operator==(std::string& pUser);
	bool operator!=(std::string& pUser);
	bool operator>(std::string& pUser);
	bool operator>=(std::string& pUser);
	bool operator<(std::string& pUser);
	bool operator<=(std::string& pUser);


	std::string getName() const {
		return _name;
	}

	std::string getSecurityKey() const {
		return _secKey;
	}
};


#endif /* USER */