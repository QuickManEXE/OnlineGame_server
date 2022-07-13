#pragma once
#include<memory>
#include<list>
#include<string>


class Base_SmartPointer {
public:
	static std::list<std::shared_ptr<Base_SmartPointer>> m_list;

	static void AddList(std::shared_ptr<Base_SmartPointer> _base);

	static void UpdateAll();

	static void CollisionCheckAll();

public:

	Base_SmartPointer(std::string _name);

	virtual void Update();

	virtual void CollisionCheck(std::shared_ptr<Base_SmartPointer> _base);

	void SetName(std::string _name) {
		m_name = _name;
	}

	std::string GetName(void) {
		return m_name;
	}

	const char* GetNameC(void) {
		return m_name.c_str();
	}

private:

	std::string m_name;

};