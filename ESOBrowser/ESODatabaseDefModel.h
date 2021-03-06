#ifndef ESO_DATABASE_DEF_MODEL_H
#define ESO_DATABASE_DEF_MODEL_H

#include <QAbstractItemModel>
#include <ESOdata/Database/ESODatabaseRecord.h>

namespace esodata {
	class ESODatabaseDef;
}
class DataStorage;

class ESODatabaseDefModel final : public QAbstractItemModel {
	Q_OBJECT

public:
	ESODatabaseDefModel(const esodata::ESODatabaseDef* def, const DataStorage *storage, QObject* parent = nullptr);
	~ESODatabaseDefModel() override;

	int columnCount(const QModelIndex& parent) const override;
	QVariant data(const QModelIndex& index, int role) const override;
	QModelIndex index(int row, int column, const QModelIndex& parent) const override;
	QModelIndex parent(const QModelIndex& index) const override;
	int rowCount(const QModelIndex& parent) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

	inline const esodata::ESODatabaseDef* def() const { return m_def; }

private:
	static std::string convertValueForDisplay(const std::monostate&);
	static std::string convertValueForDisplay(long long val);
	static std::string convertValueForDisplay(unsigned long long val);
	static std::string convertValueForDisplay(const esodata::ESODatabaseRecord::ValueEnum& val);
	static std::string convertValueForDisplay(const esodata::ESODatabaseRecord::ValueArray& val);
	static std::string convertValueForDisplay(const esodata::ESODatabaseRecord::ValueForeignKey& val);
	static std::string convertValueForDisplay(const std::string& val);
	static std::string convertValueForDisplay(bool val);
	static std::string convertValueForDisplay(double val);
	static std::string convertValueForDisplay(const esodata::ESODatabaseRecord::ValueAssetReference& val);
	static std::string convertValueForDisplay(const esodata::ESODatabaseRecord::ValueStruct & val);
	static std::string convertValueForDisplay(const esodata::ESODatabaseRecord::ValuePolymorphicReference& val);
	
	const esodata::ESODatabaseDef* m_def;
	const DataStorage* m_storage;
};

#endif
