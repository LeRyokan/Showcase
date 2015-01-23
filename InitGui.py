# ShowcaseMod gui init module
# (c) 2001 Juergen Riegel LGPL

class ShowcaseModWorkbench ( Workbench ):
	"ShowcaseMod workbench object"
	MenuText = "ShowcaseMod"
	ToolTip = "ShowcaseMod workbench"
	def Initialize(self):
		# load the module
		import ShowcaseModGui
	def GetClassName(self):
		return "ShowcaseModGui::Workbench"

Gui.addWorkbench(ShowcaseModWorkbench())
