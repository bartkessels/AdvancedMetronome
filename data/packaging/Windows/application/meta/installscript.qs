function Component(){}

Component.prototype.createOperations = function()
{
	component.createOperations();
	
	if (systemInfo.productType == "windows") {
		component.addOperation("CreateShortcut", "@TargetDir@/advancedmetronome.exe", "@StartMenuDir@/Advanced Metronome.lnk",
			"workingDirectory=@TargetDir@", "description=Launch Advanced Metronome");
	}
}
