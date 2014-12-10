import Editor 1.0
import QtQuick 1.0


Rectangle
{
	objectName: "mainWindow"
	id: mainWindow
	width: 360
	height: 400

	EditExtension {
		objectName: "objEditor01"
		id: objEditor01
		text: "This is a Editor"
		width: 360
		height: 400
	}
	
}