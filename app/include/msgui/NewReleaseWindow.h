#pragma once

#include <msgwidget/GithubRelease.h>

#include <QMainWindow>
#include <QLabel>
#include <QPlainTextEdit>

namespace msgui {

class NewReleaseWindow : public QMainWindow
{
	Q_OBJECT
public:
	NewReleaseWindow();
	~NewReleaseWindow();

	static NewReleaseWindow* instance();

	void setInfo(msgwidget::GithubReleaseInfo info);
private:
	static NewReleaseWindow* _instance;

	QLabel *_name;
	QLabel *_version;
	QPlainTextEdit *_body;
	QLabel *_link;

	msgwidget::GithubReleaseInfo _info;
};

}