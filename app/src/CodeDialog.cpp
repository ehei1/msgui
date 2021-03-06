#include "msgui/CodeDialog.h"

#include <mredit/margin/MarginStacker.h>

#include <QBoxLayout>
#include <QPushButton>
#include <QDesktopWidget>

namespace msgui {

CodeDialog::CodeDialog(itf::Configuration *configuration, const QString &code, QWidget *parent) :
	QDialog(parent), _configuration(configuration)
{
	setWindowTitle("Settings");

	QVBoxLayout *layout = new QVBoxLayout;
	setLayout(layout);

	_editor = new mredit::Editor(this);
	_editor->marginStacker()->setVisible(mredit::Global::Margin::BookmarkMargin, true);
	_editor->marginStacker()->setVisible(mredit::Global::Margin::NumberMargin, true);
	_editor->marginStacker()->setVisible(mredit::Global::Margin::SpaceMargin, true);

	_editor->setText(code);
	_configuration->createCPPHighligher(_editor->document());
	layout->addWidget(_editor);

	// buttons
	QHBoxLayout *btnlayout = new QHBoxLayout;
	layout->addLayout(btnlayout);

	QPushButton *btnOk = new QPushButton(tr("Ok"), this);
	connect(btnOk, &QPushButton::clicked, this, &CodeDialog::onBtnOk);
	QPushButton *btnCancel = new QPushButton(tr("Cancel"), this);
	connect(btnCancel, &QPushButton::clicked, this, &CodeDialog::onBtnCancel);

	btnlayout->addWidget(btnOk);
	btnlayout->addWidget(btnCancel);

	resize(QDesktopWidget().availableGeometry(this).size() * 0.7);
}

QString CodeDialog::text() const
{
	return _editor->text();
}

void CodeDialog::onBtnOk()
{
	accept();
}

void CodeDialog::onBtnCancel()
{
	reject();
}

void CodeDialog::keyPressEvent(QKeyEvent *e)
{
	if (e->key() != Qt::Key_Escape) {
		QDialog::keyPressEvent(e);
	}
}


}