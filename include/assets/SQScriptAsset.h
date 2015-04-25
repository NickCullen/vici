#ifndef V_SQSCRIPT_ASSET
#define V_SQSCRIPT_ASSET

#include "Asset.h"

class SQScriptAsset : public Asset
{
private:
	char _script_file[256];	/**< The script file */

public:
	/**
	* Default constructor
	*/
	SQScriptAsset();

	/**
	* Default destructor
	*/
	~SQScriptAsset();

	/**
	* Loads the script from the asset node
	* @param node The asset node
	*/
	virtual void Load(XmlNode& node);

	/**
	* Unload the script from memory
	*/
	virtual void Unload();

	static AssetRegister<SQScriptAsset> reg; /**< Static register for this asset type*/
};








#endif