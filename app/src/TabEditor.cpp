#include "msgui/TabEditor.h"

#include <mredit/margin/MarginStacker.h>

#include <QFileInfo>

namespace msgui {

TabEditor::TabEditor(itf::Configuration *configuration, QWidget *parent) :
	mredit::Editor(parent), _configuration(configuration), _currentFilename(), _currentFilesize(0)
{
	setReadOnly(true);
	_configuration->createCPPHighligher(document());

	marginStacker()->setVisible(mredit::Global::Margin::BookmarkMargin, true);
	marginStacker()->setVisible(mredit::Global::Margin::NumberMargin, true);
	marginStacker()->setVisible(mredit::Global::Margin::SpaceMargin, true);

	// create a bookmark group to show current line position with right arrow and yellow background
	_editor_bmgroup_showpos = bookmarkGroups().addGroup("Position", QIcon(":/arrow-right.png"));
	QTextBlockFormat spformat;
	spformat.setBackground(QColor(Qt::yellow));
	bookmarkGroups().getGroup(_editor_bmgroup_showpos)->setTextBlockFormat(spformat);
}


void TabEditor::clearMarkSourceCode()
{
	clearBookmarks(_editor_bmgroup_showpos);
}

void TabEditor::markSourceFile(int row, int col)
{
	clearMarkSourceCode();
	if (row >= 0)
	{
		setBookmark(_editor_bmgroup_showpos, row, true);
		ensureLineCenter(row, col);
	}
}

const QString &TabEditor::currentFilename() const
{
	return _currentFilename;
}

void TabEditor::setCurrentFilename(const QString &filename)
{
	_currentFilename = filename;
}

void TabEditor::openFileIfChanged(const QString &filename)
{
	QFileInfo fi(filename);
	if (fi.size() == _currentFilesize)
		return;
	_currentFilesize = fi.size();
	openFile(filename);
}

void TabEditor::setPlainTextResetSize(const QString &text)
{
	_currentFilesize = 0;
	setPlainText(text);
}

void TabEditor::onProjectChanged()
{
	// change highligther
	_configuration->createCPPHighligher(document());
}

}