#include "ESODatabaseDefModel.h"
#include <ESOdata/Database/ESODatabaseDef.h>
#include "DataStorage.h"

ESODatabaseDefModel::ESODatabaseDefModel(const esodata::ESODatabaseDef* def, const DataStorage* storage, QObject* parent) : QAbstractItemModel(parent), m_def(def), m_storage(storage) {

}

ESODatabaseDefModel::~ESODatabaseDefModel() = default;


int ESODatabaseDefModel::columnCount(const QModelIndex& parent) const {
	if (parent.isValid())
		return 0;

	return m_storage->defFieldsAsColumns().size();
}

QVariant ESODatabaseDefModel::data(const QModelIndex& index, int role) const {
	auto record = static_cast<esodata::ESODatabaseRecord *>(index.internalPointer());

	switch (role) {
	case Qt::DisplayRole:
		return QString::fromStdString(std::visit([](const auto& data) { return convertValueForDisplay(data); }, record->findField(m_storage->defFieldsAsColumns()[index.column()])));

	default:
		return QVariant();
	}

	return QVariant();
}

QModelIndex ESODatabaseDefModel::index(int row, int column, const QModelIndex& parent) const {
	if (parent.isValid() || column >= m_storage->defFieldsAsColumns().size())
		return QModelIndex();

	return createIndex(row, column, const_cast<esodata::ESODatabaseRecord *>(&m_def->records()[row]));
}

QModelIndex ESODatabaseDefModel::parent(const QModelIndex& index) const {
	(void)index;

	return QModelIndex();
}

int ESODatabaseDefModel::rowCount(const QModelIndex& parent) const {
	if(parent.isValid())
		return 0;

	return static_cast<int>(m_def->records().size());
}

std::string ESODatabaseDefModel::convertValueForDisplay(const std::monostate&) {
	return "<nil>";
}

std::string ESODatabaseDefModel::convertValueForDisplay(long long val) {
	return std::to_string(val);
}

std::string ESODatabaseDefModel::convertValueForDisplay(unsigned long long val) {
	return std::to_string(val);
}

std::string ESODatabaseDefModel::convertValueForDisplay(double val) {
	return std::to_string(val);
}

std::string ESODatabaseDefModel::convertValueForDisplay(const esodata::ESODatabaseRecord::ValueArray& val) {
	(void)val;
	return "<array>";
}

std::string ESODatabaseDefModel::convertValueForDisplay(const esodata::ESODatabaseRecord::ValueForeignKey& val) {
	(void)val;
	return "<fk>";
}

std::string ESODatabaseDefModel::convertValueForDisplay(const esodata::ESODatabaseRecord::ValueEnum& val) {
	if (std::find(val.definition->values.begin(), val.definition->values.end(), val.value) == val.definition->values.end()) {
		return val.definition->name + "::<INVALID ENUM VALUE " + std::to_string(val.value) + ">";
	}
	else {
		auto it = val.definition->valueNames.find(val.value);
		if (it == val.definition->valueNames.end()) {
			return val.definition->name + "::" + std::to_string(val.value);
		}
		else {
			return val.definition->name + "::" + it->second;
		}
	}
}

std::string ESODatabaseDefModel::convertValueForDisplay(const std::string& val) {
	return val;
}

QVariant ESODatabaseDefModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if (orientation == Qt::Orientation::Horizontal && role == Qt::DisplayRole) {
		return QString::fromStdString(m_storage->defFieldsAsColumns()[section]);
	}
	else {
		return QVariant();
	}
}

std::string ESODatabaseDefModel::convertValueForDisplay(bool val) {
	return val ? "true" : "false";
}

std::string ESODatabaseDefModel::convertValueForDisplay(const esodata::ESODatabaseRecord::ValueAssetReference& val) {
	return "<asset>";
}

std::string ESODatabaseDefModel::convertValueForDisplay(const esodata::ESODatabaseRecord::ValueStruct& val) {
	return "<struct>";
}

std::string ESODatabaseDefModel::convertValueForDisplay(const esodata::ESODatabaseRecord::ValuePolymorphicReference& val) {
	return "<polyref>";
}
