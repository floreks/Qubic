#include "department.h"

QString Department:: ID = "ID";
QString Department:: DEPARTMENTNAME = "DEPARTMENTNAME";
QString Department:: CLASSNAME = "Department";
bool Department:: isRegistered = false;

Department::Department() {
	if(!isRegistered) {
		qRegisterMetaType<Department>("Department");
		isRegistered = true;
	}
	this->id = -1;
}

Department::Department(qint32 id, QString departmentname) {
	if(!isRegistered) {
		qRegisterMetaType<Department>("Department");
		isRegistered = true;
	}
	this->id=id;
	this->departmentname=departmentname;
}

Department::Department(QString departmentname) {
	if(!isRegistered) {
		qRegisterMetaType<Department>("Department");
		isRegistered = true;
	}
	this->departmentname=departmentname;
	this->id = -1;
}

Department::Department(const Department& other) {
	id=other.id;
	departmentname=other.departmentname;
}

QString Department::getDepartmentname()const {
	return departmentname;
}

void Department::setDepartmentname(QString departmentname) {
	this->departmentname=departmentname;
}

QList<QbPersistable*> Department::getPointers() {
	return QList<QbPersistable*>();
}

QList<QbPersistable*> Department::getEmployees() {
	return QbAdvancedQueryHelper::queryManyToMany("Employee", "Department", "assignment", id);
}

