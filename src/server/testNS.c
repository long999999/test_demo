/* WARNING: This is a generated file.
 * Any manual changes will be overwritten. */

#include "testNS.h"


/* Led - ns=1;i=5003 */

static UA_StatusCode function_testNS_0_begin(UA_Server *server, UA_UInt16* ns) {
UA_StatusCode retVal = UA_STATUSCODE_GOOD;
UA_ObjectAttributes attr = UA_ObjectAttributes_default;
attr.displayName = UA_LOCALIZEDTEXT("", "Led");
retVal |= UA_Server_addNode_begin(server, UA_NODECLASS_OBJECT,
UA_NODEID_NUMERIC(ns[1], 5003),
UA_NODEID_NUMERIC(ns[0], 85),
UA_NODEID_NUMERIC(ns[0], 35),
UA_QUALIFIEDNAME(ns[1], "Led"),
UA_NODEID_NUMERIC(ns[0], 58),
(const UA_NodeAttributes*)&attr, &UA_TYPES[UA_TYPES_OBJECTATTRIBUTES],NULL, NULL);
return retVal;
}

static UA_StatusCode function_testNS_0_finish(UA_Server *server, UA_UInt16* ns) {
return UA_Server_addNode_finish(server, 
UA_NODEID_NUMERIC(ns[1], 5003)
);
}

/* Val2 - ns=1;i=6009 */

static UA_StatusCode function_testNS_1_begin(UA_Server *server, UA_UInt16* ns) {
UA_StatusCode retVal = UA_STATUSCODE_GOOD;
UA_VariableAttributes attr = UA_VariableAttributes_default;
attr.minimumSamplingInterval = 0.000000;
attr.userAccessLevel = 1;
attr.accessLevel = 3;
/* Value rank inherited */
attr.valueRank = -1;
attr.dataType = UA_NODEID_NUMERIC(ns[0], 11);
UA_Double *variablenode_ns_1_i_6009_variant_DataContents =  UA_Double_new();
if (!variablenode_ns_1_i_6009_variant_DataContents) return UA_STATUSCODE_BADOUTOFMEMORY;
UA_Double_init(variablenode_ns_1_i_6009_variant_DataContents);
*variablenode_ns_1_i_6009_variant_DataContents = (UA_Double) 47.5;
UA_Variant_setScalar(&attr.value, variablenode_ns_1_i_6009_variant_DataContents, &UA_TYPES[UA_TYPES_DOUBLE]);
attr.displayName = UA_LOCALIZEDTEXT("", "Val2");
retVal |= UA_Server_addNode_begin(server, UA_NODECLASS_VARIABLE,
UA_NODEID_NUMERIC(ns[1], 6009),
UA_NODEID_NUMERIC(ns[1], 5003),
UA_NODEID_NUMERIC(ns[0], 47),
UA_QUALIFIEDNAME(ns[1], "Val2"),
UA_NODEID_NUMERIC(ns[0], 63),
(const UA_NodeAttributes*)&attr, &UA_TYPES[UA_TYPES_VARIABLEATTRIBUTES],NULL, NULL);
UA_Double_delete(variablenode_ns_1_i_6009_variant_DataContents);
return retVal;
}

static UA_StatusCode function_testNS_1_finish(UA_Server *server, UA_UInt16* ns) {
return UA_Server_addNode_finish(server, 
UA_NODEID_NUMERIC(ns[1], 6009)
);
}

/* Remote - ns=1;i=7002 */

static UA_StatusCode function_testNS_2_begin(UA_Server *server, UA_UInt16* ns) {
#ifdef UA_ENABLE_METHODCALLS
UA_StatusCode retVal = UA_STATUSCODE_GOOD;
UA_MethodAttributes attr = UA_MethodAttributes_default;
attr.executable = true;
attr.userExecutable = true;
attr.displayName = UA_LOCALIZEDTEXT("", "Remote");
retVal |= UA_Server_addNode_begin(server, UA_NODECLASS_METHOD,
UA_NODEID_NUMERIC(ns[1], 7002),
UA_NODEID_NUMERIC(ns[1], 5003),
UA_NODEID_NUMERIC(ns[0], 47),
UA_QUALIFIEDNAME(ns[1], "Remote"),
 UA_NODEID_NULL,
(const UA_NodeAttributes*)&attr, &UA_TYPES[UA_TYPES_METHODATTRIBUTES],NULL, NULL);
return retVal;
#else
return UA_STATUSCODE_GOOD;
#endif /* UA_ENABLE_METHODCALLS */
}

static UA_StatusCode function_testNS_2_finish(UA_Server *server, UA_UInt16* ns) {
#ifdef UA_ENABLE_METHODCALLS
return UA_Server_addMethodNode_finish(server, 
UA_NODEID_NUMERIC(ns[1], 7002)
, NULL, 0, NULL, 0, NULL);
#else
return UA_STATUSCODE_GOOD;
#endif /* UA_ENABLE_METHODCALLS */
}

/* OutputArguments - ns=1;i=6011 */

static UA_StatusCode function_testNS_3_begin(UA_Server *server, UA_UInt16* ns) {
UA_StatusCode retVal = UA_STATUSCODE_GOOD;
UA_VariableAttributes attr = UA_VariableAttributes_default;
attr.minimumSamplingInterval = 0.000000;
attr.userAccessLevel = 1;
attr.accessLevel = 1;
attr.valueRank = 1;
attr.arrayDimensionsSize = 1;
UA_UInt32 arrayDimensions[1];
arrayDimensions[0] = 1;
attr.arrayDimensions = &arrayDimensions[0];
attr.dataType = UA_NODEID_NUMERIC(ns[0], 296);
UA_Argument variablenode_ns_1_i_6011_variant_DataContents[1];

UA_init(&variablenode_ns_1_i_6011_variant_DataContents[0], &UA_TYPES[UA_TYPES_ARGUMENT]);
variablenode_ns_1_i_6011_variant_DataContents[0].name = UA_STRING("Input2");
variablenode_ns_1_i_6011_variant_DataContents[0].dataType = UA_NODEID_NUMERIC(ns[0], 7);
variablenode_ns_1_i_6011_variant_DataContents[0].valueRank = (UA_Int32) -1;
UA_Variant_setArray(&attr.value, &variablenode_ns_1_i_6011_variant_DataContents, (UA_Int32) 1, &UA_TYPES[UA_TYPES_ARGUMENT]);
attr.displayName = UA_LOCALIZEDTEXT("", "OutputArguments");
retVal |= UA_Server_addNode_begin(server, UA_NODECLASS_VARIABLE,
UA_NODEID_NUMERIC(ns[1], 6011),
UA_NODEID_NUMERIC(ns[1], 7002),
UA_NODEID_NUMERIC(ns[0], 46),
UA_QUALIFIEDNAME(ns[0], "OutputArguments"),
UA_NODEID_NUMERIC(ns[0], 68),
(const UA_NodeAttributes*)&attr, &UA_TYPES[UA_TYPES_VARIABLEATTRIBUTES],NULL, NULL);

return retVal;
}

static UA_StatusCode function_testNS_3_finish(UA_Server *server, UA_UInt16* ns) {
return UA_Server_addNode_finish(server, 
UA_NODEID_NUMERIC(ns[1], 6011)
);
}

/* InputArguments - ns=1;i=6010 */

static UA_StatusCode function_testNS_4_begin(UA_Server *server, UA_UInt16* ns) {
UA_StatusCode retVal = UA_STATUSCODE_GOOD;
UA_VariableAttributes attr = UA_VariableAttributes_default;
attr.minimumSamplingInterval = 0.000000;
attr.userAccessLevel = 1;
attr.accessLevel = 1;
attr.valueRank = 1;
attr.arrayDimensionsSize = 1;
UA_UInt32 arrayDimensions[1];
arrayDimensions[0] = 1;
attr.arrayDimensions = &arrayDimensions[0];
attr.dataType = UA_NODEID_NUMERIC(ns[0], 296);
UA_Argument variablenode_ns_1_i_6010_variant_DataContents[1];

UA_init(&variablenode_ns_1_i_6010_variant_DataContents[0], &UA_TYPES[UA_TYPES_ARGUMENT]);
variablenode_ns_1_i_6010_variant_DataContents[0].name = UA_STRING("Input1");
variablenode_ns_1_i_6010_variant_DataContents[0].dataType = UA_NODEID_NUMERIC(ns[0], 7);
variablenode_ns_1_i_6010_variant_DataContents[0].valueRank = (UA_Int32) -1;
UA_Variant_setArray(&attr.value, &variablenode_ns_1_i_6010_variant_DataContents, (UA_Int32) 1, &UA_TYPES[UA_TYPES_ARGUMENT]);
attr.displayName = UA_LOCALIZEDTEXT("", "InputArguments");
retVal |= UA_Server_addNode_begin(server, UA_NODECLASS_VARIABLE,
UA_NODEID_NUMERIC(ns[1], 6010),
UA_NODEID_NUMERIC(ns[1], 7002),
UA_NODEID_NUMERIC(ns[0], 46),
UA_QUALIFIEDNAME(ns[0], "InputArguments"),
UA_NODEID_NUMERIC(ns[0], 68),
(const UA_NodeAttributes*)&attr, &UA_TYPES[UA_TYPES_VARIABLEATTRIBUTES],NULL, NULL);

return retVal;
}

static UA_StatusCode function_testNS_4_finish(UA_Server *server, UA_UInt16* ns) {
return UA_Server_addNode_finish(server, 
UA_NODEID_NUMERIC(ns[1], 6010)
);
}

/* Val1 - ns=1;i=6008 */

static UA_StatusCode function_testNS_5_begin(UA_Server *server, UA_UInt16* ns) {
UA_StatusCode retVal = UA_STATUSCODE_GOOD;
UA_VariableAttributes attr = UA_VariableAttributes_default;
attr.minimumSamplingInterval = 0.000000;
attr.userAccessLevel = 1;
attr.accessLevel = 3;
/* Value rank inherited */
attr.valueRank = -1;
attr.dataType = UA_NODEID_NUMERIC(ns[0], 11);
UA_Double *variablenode_ns_1_i_6008_variant_DataContents =  UA_Double_new();
if (!variablenode_ns_1_i_6008_variant_DataContents) return UA_STATUSCODE_BADOUTOFMEMORY;
UA_Double_init(variablenode_ns_1_i_6008_variant_DataContents);
*variablenode_ns_1_i_6008_variant_DataContents = (UA_Double) 21.2;
UA_Variant_setScalar(&attr.value, variablenode_ns_1_i_6008_variant_DataContents, &UA_TYPES[UA_TYPES_DOUBLE]);
attr.displayName = UA_LOCALIZEDTEXT("", "Val1");
retVal |= UA_Server_addNode_begin(server, UA_NODECLASS_VARIABLE,
UA_NODEID_NUMERIC(ns[1], 6008),
UA_NODEID_NUMERIC(ns[1], 5003),
UA_NODEID_NUMERIC(ns[0], 47),
UA_QUALIFIEDNAME(ns[1], "Val1"),
UA_NODEID_NUMERIC(ns[0], 63),
(const UA_NodeAttributes*)&attr, &UA_TYPES[UA_TYPES_VARIABLEATTRIBUTES],NULL, NULL);
UA_Double_delete(variablenode_ns_1_i_6008_variant_DataContents);
return retVal;
}

static UA_StatusCode function_testNS_5_finish(UA_Server *server, UA_UInt16* ns) {
return UA_Server_addNode_finish(server, 
UA_NODEID_NUMERIC(ns[1], 6008)
);
}

/* MyObjectType - ns=1;i=1002 */

static UA_StatusCode function_testNS_6_begin(UA_Server *server, UA_UInt16* ns) {
UA_StatusCode retVal = UA_STATUSCODE_GOOD;
UA_ObjectTypeAttributes attr = UA_ObjectTypeAttributes_default;
attr.displayName = UA_LOCALIZEDTEXT("", "MyObjectType");
retVal |= UA_Server_addNode_begin(server, UA_NODECLASS_OBJECTTYPE,
UA_NODEID_NUMERIC(ns[1], 1002),
UA_NODEID_NUMERIC(ns[0], 58),
UA_NODEID_NUMERIC(ns[0], 45),
UA_QUALIFIEDNAME(ns[1], "MyObjectType"),
 UA_NODEID_NULL,
(const UA_NodeAttributes*)&attr, &UA_TYPES[UA_TYPES_OBJECTTYPEATTRIBUTES],NULL, NULL);
return retVal;
}

static UA_StatusCode function_testNS_6_finish(UA_Server *server, UA_UInt16* ns) {
return UA_Server_addNode_finish(server, 
UA_NODEID_NUMERIC(ns[1], 1002)
);
}

/* Var1 - ns=1;i=6001 */

static UA_StatusCode function_testNS_7_begin(UA_Server *server, UA_UInt16* ns) {
UA_StatusCode retVal = UA_STATUSCODE_GOOD;
UA_VariableAttributes attr = UA_VariableAttributes_default;
attr.minimumSamplingInterval = 0.000000;
attr.userAccessLevel = 1;
attr.accessLevel = 3;
/* Value rank inherited */
attr.valueRank = -1;
attr.dataType = UA_NODEID_NUMERIC(ns[0], 6);
attr.displayName = UA_LOCALIZEDTEXT("", "Var1");
retVal |= UA_Server_addNode_begin(server, UA_NODECLASS_VARIABLE,
UA_NODEID_NUMERIC(ns[1], 6001),
UA_NODEID_NUMERIC(ns[1], 1002),
UA_NODEID_NUMERIC(ns[0], 47),
UA_QUALIFIEDNAME(ns[1], "Var1"),
UA_NODEID_NUMERIC(ns[0], 63),
(const UA_NodeAttributes*)&attr, &UA_TYPES[UA_TYPES_VARIABLEATTRIBUTES],NULL, NULL);
retVal |= UA_Server_addReference(server, UA_NODEID_NUMERIC(ns[1], 6001), UA_NODEID_NUMERIC(ns[0], 37), UA_EXPANDEDNODEID_NUMERIC(ns[0], 78), true);
return retVal;
}

static UA_StatusCode function_testNS_7_finish(UA_Server *server, UA_UInt16* ns) {
return UA_Server_addNode_finish(server, 
UA_NODEID_NUMERIC(ns[1], 6001)
);
}

/* Func - ns=1;i=7001 */

static UA_StatusCode function_testNS_8_begin(UA_Server *server, UA_UInt16* ns) {
#ifdef UA_ENABLE_METHODCALLS
UA_StatusCode retVal = UA_STATUSCODE_GOOD;
UA_MethodAttributes attr = UA_MethodAttributes_default;
attr.executable = true;
attr.userExecutable = true;
attr.displayName = UA_LOCALIZEDTEXT("", "Func");
retVal |= UA_Server_addNode_begin(server, UA_NODECLASS_METHOD,
UA_NODEID_NUMERIC(ns[1], 7001),
UA_NODEID_NUMERIC(ns[1], 1002),
UA_NODEID_NUMERIC(ns[0], 47),
UA_QUALIFIEDNAME(ns[1], "Func"),
 UA_NODEID_NULL,
(const UA_NodeAttributes*)&attr, &UA_TYPES[UA_TYPES_METHODATTRIBUTES],NULL, NULL);
retVal |= UA_Server_addReference(server, UA_NODEID_NUMERIC(ns[1], 7001), UA_NODEID_NUMERIC(ns[0], 37), UA_EXPANDEDNODEID_NUMERIC(ns[0], 78), true);
return retVal;
#else
return UA_STATUSCODE_GOOD;
#endif /* UA_ENABLE_METHODCALLS */
}

static UA_StatusCode function_testNS_8_finish(UA_Server *server, UA_UInt16* ns) {
#ifdef UA_ENABLE_METHODCALLS
return UA_Server_addMethodNode_finish(server, 
UA_NODEID_NUMERIC(ns[1], 7001)
, NULL, 0, NULL, 0, NULL);
#else
return UA_STATUSCODE_GOOD;
#endif /* UA_ENABLE_METHODCALLS */
}

/* OutputArguments - ns=1;i=6004 */

static UA_StatusCode function_testNS_9_begin(UA_Server *server, UA_UInt16* ns) {
UA_StatusCode retVal = UA_STATUSCODE_GOOD;
UA_VariableAttributes attr = UA_VariableAttributes_default;
attr.minimumSamplingInterval = 0.000000;
attr.userAccessLevel = 1;
attr.accessLevel = 1;
attr.valueRank = 1;
attr.arrayDimensionsSize = 1;
UA_UInt32 arrayDimensions[1];
arrayDimensions[0] = 1;
attr.arrayDimensions = &arrayDimensions[0];
attr.dataType = UA_NODEID_NUMERIC(ns[0], 296);
UA_Argument variablenode_ns_1_i_6004_variant_DataContents[1];

UA_init(&variablenode_ns_1_i_6004_variant_DataContents[0], &UA_TYPES[UA_TYPES_ARGUMENT]);
variablenode_ns_1_i_6004_variant_DataContents[0].name = UA_STRING("output0");
variablenode_ns_1_i_6004_variant_DataContents[0].dataType = UA_NODEID_NUMERIC(ns[0], 7);
variablenode_ns_1_i_6004_variant_DataContents[0].valueRank = (UA_Int32) -1;
UA_Variant_setArray(&attr.value, &variablenode_ns_1_i_6004_variant_DataContents, (UA_Int32) 1, &UA_TYPES[UA_TYPES_ARGUMENT]);
attr.displayName = UA_LOCALIZEDTEXT("", "OutputArguments");
retVal |= UA_Server_addNode_begin(server, UA_NODECLASS_VARIABLE,
UA_NODEID_NUMERIC(ns[1], 6004),
UA_NODEID_NUMERIC(ns[1], 7001),
UA_NODEID_NUMERIC(ns[0], 46),
UA_QUALIFIEDNAME(ns[0], "OutputArguments"),
UA_NODEID_NUMERIC(ns[0], 68),
(const UA_NodeAttributes*)&attr, &UA_TYPES[UA_TYPES_VARIABLEATTRIBUTES],NULL, NULL);

retVal |= UA_Server_addReference(server, UA_NODEID_NUMERIC(ns[1], 6004), UA_NODEID_NUMERIC(ns[0], 37), UA_EXPANDEDNODEID_NUMERIC(ns[0], 78), true);
return retVal;
}

static UA_StatusCode function_testNS_9_finish(UA_Server *server, UA_UInt16* ns) {
return UA_Server_addNode_finish(server, 
UA_NODEID_NUMERIC(ns[1], 6004)
);
}

/* InputArguments - ns=1;i=6003 */

static UA_StatusCode function_testNS_10_begin(UA_Server *server, UA_UInt16* ns) {
UA_StatusCode retVal = UA_STATUSCODE_GOOD;
UA_VariableAttributes attr = UA_VariableAttributes_default;
attr.minimumSamplingInterval = 0.000000;
attr.userAccessLevel = 1;
attr.accessLevel = 1;
attr.valueRank = 1;
attr.arrayDimensionsSize = 1;
UA_UInt32 arrayDimensions[1];
arrayDimensions[0] = 2;
attr.arrayDimensions = &arrayDimensions[0];
attr.dataType = UA_NODEID_NUMERIC(ns[0], 296);
UA_Argument variablenode_ns_1_i_6003_variant_DataContents[2];

UA_init(&variablenode_ns_1_i_6003_variant_DataContents[0], &UA_TYPES[UA_TYPES_ARGUMENT]);
variablenode_ns_1_i_6003_variant_DataContents[0].name = UA_STRING("input0");
variablenode_ns_1_i_6003_variant_DataContents[0].dataType = UA_NODEID_NUMERIC(ns[0], 7);
variablenode_ns_1_i_6003_variant_DataContents[0].valueRank = (UA_Int32) -1;

UA_init(&variablenode_ns_1_i_6003_variant_DataContents[1], &UA_TYPES[UA_TYPES_ARGUMENT]);
variablenode_ns_1_i_6003_variant_DataContents[1].name = UA_STRING("input1");
variablenode_ns_1_i_6003_variant_DataContents[1].dataType = UA_NODEID_NUMERIC(ns[0], 7);
variablenode_ns_1_i_6003_variant_DataContents[1].valueRank = (UA_Int32) -1;
UA_Variant_setArray(&attr.value, &variablenode_ns_1_i_6003_variant_DataContents, (UA_Int32) 2, &UA_TYPES[UA_TYPES_ARGUMENT]);
attr.displayName = UA_LOCALIZEDTEXT("", "InputArguments");
retVal |= UA_Server_addNode_begin(server, UA_NODECLASS_VARIABLE,
UA_NODEID_NUMERIC(ns[1], 6003),
UA_NODEID_NUMERIC(ns[1], 7001),
UA_NODEID_NUMERIC(ns[0], 46),
UA_QUALIFIEDNAME(ns[0], "InputArguments"),
UA_NODEID_NUMERIC(ns[0], 68),
(const UA_NodeAttributes*)&attr, &UA_TYPES[UA_TYPES_VARIABLEATTRIBUTES],NULL, NULL);


retVal |= UA_Server_addReference(server, UA_NODEID_NUMERIC(ns[1], 6003), UA_NODEID_NUMERIC(ns[0], 37), UA_EXPANDEDNODEID_NUMERIC(ns[0], 78), true);
return retVal;
}

static UA_StatusCode function_testNS_10_finish(UA_Server *server, UA_UInt16* ns) {
return UA_Server_addNode_finish(server, 
UA_NODEID_NUMERIC(ns[1], 6003)
);
}

/* Var2 - ns=1;i=6002 */

static UA_StatusCode function_testNS_11_begin(UA_Server *server, UA_UInt16* ns) {
UA_StatusCode retVal = UA_STATUSCODE_GOOD;
UA_VariableAttributes attr = UA_VariableAttributes_default;
attr.minimumSamplingInterval = 0.000000;
attr.userAccessLevel = 1;
attr.accessLevel = 3;
/* Value rank inherited */
attr.valueRank = -1;
attr.dataType = UA_NODEID_NUMERIC(ns[0], 6);
attr.displayName = UA_LOCALIZEDTEXT("", "Var2");
retVal |= UA_Server_addNode_begin(server, UA_NODECLASS_VARIABLE,
UA_NODEID_NUMERIC(ns[1], 6002),
UA_NODEID_NUMERIC(ns[1], 1002),
UA_NODEID_NUMERIC(ns[0], 47),
UA_QUALIFIEDNAME(ns[1], "Var2"),
UA_NODEID_NUMERIC(ns[0], 63),
(const UA_NodeAttributes*)&attr, &UA_TYPES[UA_TYPES_VARIABLEATTRIBUTES],NULL, NULL);
retVal |= UA_Server_addReference(server, UA_NODEID_NUMERIC(ns[1], 6002), UA_NODEID_NUMERIC(ns[0], 37), UA_EXPANDEDNODEID_NUMERIC(ns[0], 78), true);
return retVal;
}

static UA_StatusCode function_testNS_11_finish(UA_Server *server, UA_UInt16* ns) {
return UA_Server_addNode_finish(server, 
UA_NODEID_NUMERIC(ns[1], 6002)
);
}

/* http://yourorganisation.org/example/ - ns=1;i=5001 */

static UA_StatusCode function_testNS_12_begin(UA_Server *server, UA_UInt16* ns) {
UA_StatusCode retVal = UA_STATUSCODE_GOOD;
UA_ObjectAttributes attr = UA_ObjectAttributes_default;
attr.displayName = UA_LOCALIZEDTEXT("", "http://yourorganisation.org/example/");
retVal |= UA_Server_addNode_begin(server, UA_NODECLASS_OBJECT,
UA_NODEID_NUMERIC(ns[1], 5001),
UA_NODEID_NUMERIC(ns[0], 11715),
UA_NODEID_NUMERIC(ns[0], 47),
UA_QUALIFIEDNAME(ns[1], "http://yourorganisation.org/example/"),
UA_NODEID_NUMERIC(ns[0], 11616),
(const UA_NodeAttributes*)&attr, &UA_TYPES[UA_TYPES_OBJECTATTRIBUTES],NULL, NULL);
return retVal;
}

static UA_StatusCode function_testNS_12_finish(UA_Server *server, UA_UInt16* ns) {
return UA_Server_addNode_finish(server, 
UA_NODEID_NUMERIC(ns[1], 5001)
);
}

/* NamespacePublicationDate - ns=1;i=6013 */

static UA_StatusCode function_testNS_13_begin(UA_Server *server, UA_UInt16* ns) {
UA_StatusCode retVal = UA_STATUSCODE_GOOD;
UA_VariableAttributes attr = UA_VariableAttributes_default;
attr.minimumSamplingInterval = 0.000000;
attr.userAccessLevel = 1;
attr.accessLevel = 1;
/* Value rank inherited */
attr.valueRank = -1;
attr.dataType = UA_NODEID_NUMERIC(ns[0], 13);
UA_DateTime *variablenode_ns_1_i_6013_variant_DataContents =  UA_DateTime_new();
if (!variablenode_ns_1_i_6013_variant_DataContents) return UA_STATUSCODE_BADOUTOFMEMORY;
UA_DateTime_init(variablenode_ns_1_i_6013_variant_DataContents);
*variablenode_ns_1_i_6013_variant_DataContents = ( (UA_DateTime)(1594024070000 * UA_DATETIME_MSEC) + UA_DATETIME_UNIX_EPOCH);
UA_Variant_setScalar(&attr.value, variablenode_ns_1_i_6013_variant_DataContents, &UA_TYPES[UA_TYPES_DATETIME]);
attr.displayName = UA_LOCALIZEDTEXT("", "NamespacePublicationDate");
retVal |= UA_Server_addNode_begin(server, UA_NODECLASS_VARIABLE,
UA_NODEID_NUMERIC(ns[1], 6013),
UA_NODEID_NUMERIC(ns[1], 5001),
UA_NODEID_NUMERIC(ns[0], 46),
UA_QUALIFIEDNAME(ns[0], "NamespacePublicationDate"),
UA_NODEID_NUMERIC(ns[0], 68),
(const UA_NodeAttributes*)&attr, &UA_TYPES[UA_TYPES_VARIABLEATTRIBUTES],NULL, NULL);
UA_DateTime_delete(variablenode_ns_1_i_6013_variant_DataContents);
return retVal;
}

static UA_StatusCode function_testNS_13_finish(UA_Server *server, UA_UInt16* ns) {
return UA_Server_addNode_finish(server, 
UA_NODEID_NUMERIC(ns[1], 6013)
);
}

/* IsNamespaceSubset - ns=1;i=6012 */

static UA_StatusCode function_testNS_14_begin(UA_Server *server, UA_UInt16* ns) {
UA_StatusCode retVal = UA_STATUSCODE_GOOD;
UA_VariableAttributes attr = UA_VariableAttributes_default;
attr.minimumSamplingInterval = 0.000000;
attr.userAccessLevel = 1;
attr.accessLevel = 1;
/* Value rank inherited */
attr.valueRank = -1;
attr.dataType = UA_NODEID_NUMERIC(ns[0], 1);
UA_Boolean *variablenode_ns_1_i_6012_variant_DataContents =  UA_Boolean_new();
if (!variablenode_ns_1_i_6012_variant_DataContents) return UA_STATUSCODE_BADOUTOFMEMORY;
UA_Boolean_init(variablenode_ns_1_i_6012_variant_DataContents);
*variablenode_ns_1_i_6012_variant_DataContents = (UA_Boolean) false;
UA_Variant_setScalar(&attr.value, variablenode_ns_1_i_6012_variant_DataContents, &UA_TYPES[UA_TYPES_BOOLEAN]);
attr.displayName = UA_LOCALIZEDTEXT("", "IsNamespaceSubset");
retVal |= UA_Server_addNode_begin(server, UA_NODECLASS_VARIABLE,
UA_NODEID_NUMERIC(ns[1], 6012),
UA_NODEID_NUMERIC(ns[1], 5001),
UA_NODEID_NUMERIC(ns[0], 46),
UA_QUALIFIEDNAME(ns[0], "IsNamespaceSubset"),
UA_NODEID_NUMERIC(ns[0], 68),
(const UA_NodeAttributes*)&attr, &UA_TYPES[UA_TYPES_VARIABLEATTRIBUTES],NULL, NULL);
UA_Boolean_delete(variablenode_ns_1_i_6012_variant_DataContents);
return retVal;
}

static UA_StatusCode function_testNS_14_finish(UA_Server *server, UA_UInt16* ns) {
return UA_Server_addNode_finish(server, 
UA_NODEID_NUMERIC(ns[1], 6012)
);
}

/* NamespaceUri - ns=1;i=6014 */

static UA_StatusCode function_testNS_15_begin(UA_Server *server, UA_UInt16* ns) {
UA_StatusCode retVal = UA_STATUSCODE_GOOD;
UA_VariableAttributes attr = UA_VariableAttributes_default;
attr.minimumSamplingInterval = 0.000000;
attr.userAccessLevel = 1;
attr.accessLevel = 1;
/* Value rank inherited */
attr.valueRank = -1;
attr.dataType = UA_NODEID_NUMERIC(ns[0], 12);
UA_String *variablenode_ns_1_i_6014_variant_DataContents =  UA_String_new();
if (!variablenode_ns_1_i_6014_variant_DataContents) return UA_STATUSCODE_BADOUTOFMEMORY;
UA_String_init(variablenode_ns_1_i_6014_variant_DataContents);
*variablenode_ns_1_i_6014_variant_DataContents = UA_STRING_ALLOC("http://yourorganisation.org/example/");
UA_Variant_setScalar(&attr.value, variablenode_ns_1_i_6014_variant_DataContents, &UA_TYPES[UA_TYPES_STRING]);
attr.displayName = UA_LOCALIZEDTEXT("", "NamespaceUri");
retVal |= UA_Server_addNode_begin(server, UA_NODECLASS_VARIABLE,
UA_NODEID_NUMERIC(ns[1], 6014),
UA_NODEID_NUMERIC(ns[1], 5001),
UA_NODEID_NUMERIC(ns[0], 46),
UA_QUALIFIEDNAME(ns[0], "NamespaceUri"),
UA_NODEID_NUMERIC(ns[0], 68),
(const UA_NodeAttributes*)&attr, &UA_TYPES[UA_TYPES_VARIABLEATTRIBUTES],NULL, NULL);
UA_String_delete(variablenode_ns_1_i_6014_variant_DataContents);
return retVal;
}

static UA_StatusCode function_testNS_15_finish(UA_Server *server, UA_UInt16* ns) {
return UA_Server_addNode_finish(server, 
UA_NODEID_NUMERIC(ns[1], 6014)
);
}

/* StaticStringNodeIdPattern - ns=1;i=6018 */

static UA_StatusCode function_testNS_16_begin(UA_Server *server, UA_UInt16* ns) {
UA_StatusCode retVal = UA_STATUSCODE_GOOD;
UA_VariableAttributes attr = UA_VariableAttributes_default;
attr.minimumSamplingInterval = 0.000000;
attr.userAccessLevel = 1;
attr.accessLevel = 1;
/* Value rank inherited */
attr.valueRank = -1;
attr.dataType = UA_NODEID_NUMERIC(ns[0], 12);
attr.displayName = UA_LOCALIZEDTEXT("", "StaticStringNodeIdPattern");
retVal |= UA_Server_addNode_begin(server, UA_NODECLASS_VARIABLE,
UA_NODEID_NUMERIC(ns[1], 6018),
UA_NODEID_NUMERIC(ns[1], 5001),
UA_NODEID_NUMERIC(ns[0], 46),
UA_QUALIFIEDNAME(ns[0], "StaticStringNodeIdPattern"),
UA_NODEID_NUMERIC(ns[0], 68),
(const UA_NodeAttributes*)&attr, &UA_TYPES[UA_TYPES_VARIABLEATTRIBUTES],NULL, NULL);
return retVal;
}

static UA_StatusCode function_testNS_16_finish(UA_Server *server, UA_UInt16* ns) {
return UA_Server_addNode_finish(server, 
UA_NODEID_NUMERIC(ns[1], 6018)
);
}

/* NamespaceVersion - ns=1;i=6015 */

static UA_StatusCode function_testNS_17_begin(UA_Server *server, UA_UInt16* ns) {
UA_StatusCode retVal = UA_STATUSCODE_GOOD;
UA_VariableAttributes attr = UA_VariableAttributes_default;
attr.minimumSamplingInterval = 0.000000;
attr.userAccessLevel = 1;
attr.accessLevel = 1;
/* Value rank inherited */
attr.valueRank = -1;
attr.dataType = UA_NODEID_NUMERIC(ns[0], 12);
UA_String *variablenode_ns_1_i_6015_variant_DataContents =  UA_String_new();
if (!variablenode_ns_1_i_6015_variant_DataContents) return UA_STATUSCODE_BADOUTOFMEMORY;
UA_String_init(variablenode_ns_1_i_6015_variant_DataContents);
*variablenode_ns_1_i_6015_variant_DataContents = UA_STRING_ALLOC("1.0.0");
UA_Variant_setScalar(&attr.value, variablenode_ns_1_i_6015_variant_DataContents, &UA_TYPES[UA_TYPES_STRING]);
attr.displayName = UA_LOCALIZEDTEXT("", "NamespaceVersion");
retVal |= UA_Server_addNode_begin(server, UA_NODECLASS_VARIABLE,
UA_NODEID_NUMERIC(ns[1], 6015),
UA_NODEID_NUMERIC(ns[1], 5001),
UA_NODEID_NUMERIC(ns[0], 46),
UA_QUALIFIEDNAME(ns[0], "NamespaceVersion"),
UA_NODEID_NUMERIC(ns[0], 68),
(const UA_NodeAttributes*)&attr, &UA_TYPES[UA_TYPES_VARIABLEATTRIBUTES],NULL, NULL);
UA_String_delete(variablenode_ns_1_i_6015_variant_DataContents);
return retVal;
}

static UA_StatusCode function_testNS_17_finish(UA_Server *server, UA_UInt16* ns) {
return UA_Server_addNode_finish(server, 
UA_NODEID_NUMERIC(ns[1], 6015)
);
}

/* StaticNumericNodeIdRange - ns=1;i=6017 */

static UA_StatusCode function_testNS_18_begin(UA_Server *server, UA_UInt16* ns) {
UA_StatusCode retVal = UA_STATUSCODE_GOOD;
UA_VariableAttributes attr = UA_VariableAttributes_default;
attr.minimumSamplingInterval = 0.000000;
attr.userAccessLevel = 1;
attr.accessLevel = 1;
attr.valueRank = 1;
attr.arrayDimensionsSize = 1;
UA_UInt32 arrayDimensions[1];
arrayDimensions[0] = 0;
attr.arrayDimensions = &arrayDimensions[0];
attr.dataType = UA_NODEID_NUMERIC(ns[0], 291);
attr.displayName = UA_LOCALIZEDTEXT("", "StaticNumericNodeIdRange");
retVal |= UA_Server_addNode_begin(server, UA_NODECLASS_VARIABLE,
UA_NODEID_NUMERIC(ns[1], 6017),
UA_NODEID_NUMERIC(ns[1], 5001),
UA_NODEID_NUMERIC(ns[0], 46),
UA_QUALIFIEDNAME(ns[0], "StaticNumericNodeIdRange"),
UA_NODEID_NUMERIC(ns[0], 68),
(const UA_NodeAttributes*)&attr, &UA_TYPES[UA_TYPES_VARIABLEATTRIBUTES],NULL, NULL);
return retVal;
}

static UA_StatusCode function_testNS_18_finish(UA_Server *server, UA_UInt16* ns) {
return UA_Server_addNode_finish(server, 
UA_NODEID_NUMERIC(ns[1], 6017)
);
}

/* StaticNodeIdTypes - ns=1;i=6016 */

static UA_StatusCode function_testNS_19_begin(UA_Server *server, UA_UInt16* ns) {
UA_StatusCode retVal = UA_STATUSCODE_GOOD;
UA_VariableAttributes attr = UA_VariableAttributes_default;
attr.minimumSamplingInterval = 0.000000;
attr.userAccessLevel = 1;
attr.accessLevel = 1;
attr.valueRank = 1;
attr.arrayDimensionsSize = 1;
UA_UInt32 arrayDimensions[1];
arrayDimensions[0] = 0;
attr.arrayDimensions = &arrayDimensions[0];
attr.dataType = UA_NODEID_NUMERIC(ns[0], 256);
attr.displayName = UA_LOCALIZEDTEXT("", "StaticNodeIdTypes");
retVal |= UA_Server_addNode_begin(server, UA_NODECLASS_VARIABLE,
UA_NODEID_NUMERIC(ns[1], 6016),
UA_NODEID_NUMERIC(ns[1], 5001),
UA_NODEID_NUMERIC(ns[0], 46),
UA_QUALIFIEDNAME(ns[0], "StaticNodeIdTypes"),
UA_NODEID_NUMERIC(ns[0], 68),
(const UA_NodeAttributes*)&attr, &UA_TYPES[UA_TYPES_VARIABLEATTRIBUTES],NULL, NULL);
return retVal;
}

static UA_StatusCode function_testNS_19_finish(UA_Server *server, UA_UInt16* ns) {
return UA_Server_addNode_finish(server, 
UA_NODEID_NUMERIC(ns[1], 6016)
);
}

/* Led - ns=1;i=5002 */

static UA_StatusCode function_testNS_20_begin(UA_Server *server, UA_UInt16* ns) {
UA_StatusCode retVal = UA_STATUSCODE_GOOD;
UA_ObjectAttributes attr = UA_ObjectAttributes_default;
attr.displayName = UA_LOCALIZEDTEXT("", "Led");
retVal |= UA_Server_addNode_begin(server, UA_NODECLASS_OBJECT,
UA_NODEID_NUMERIC(ns[1], 5002),
UA_NODEID_NUMERIC(ns[0], 85),
UA_NODEID_NUMERIC(ns[0], 35),
UA_QUALIFIEDNAME(ns[1], "Led"),
UA_NODEID_NUMERIC(ns[0], 58),
(const UA_NodeAttributes*)&attr, &UA_TYPES[UA_TYPES_OBJECTATTRIBUTES],NULL, NULL);
return retVal;
}

static UA_StatusCode function_testNS_20_finish(UA_Server *server, UA_UInt16* ns) {
return UA_Server_addNode_finish(server, 
UA_NODEID_NUMERIC(ns[1], 5002)
);
}

/* Va1 - ns=1;i=6005 */

static UA_StatusCode function_testNS_21_begin(UA_Server *server, UA_UInt16* ns) {
UA_StatusCode retVal = UA_STATUSCODE_GOOD;
UA_VariableAttributes attr = UA_VariableAttributes_default;
attr.minimumSamplingInterval = 0.000000;
attr.userAccessLevel = 1;
attr.accessLevel = 3;
/* Value rank inherited */
attr.valueRank = -1;
attr.dataType = UA_NODEID_NUMERIC(ns[0], 11);
UA_Double *variablenode_ns_1_i_6005_variant_DataContents =  UA_Double_new();
if (!variablenode_ns_1_i_6005_variant_DataContents) return UA_STATUSCODE_BADOUTOFMEMORY;
UA_Double_init(variablenode_ns_1_i_6005_variant_DataContents);
*variablenode_ns_1_i_6005_variant_DataContents = (UA_Double) 12.5;
UA_Variant_setScalar(&attr.value, variablenode_ns_1_i_6005_variant_DataContents, &UA_TYPES[UA_TYPES_DOUBLE]);
attr.displayName = UA_LOCALIZEDTEXT("", "Va1");
retVal |= UA_Server_addNode_begin(server, UA_NODECLASS_VARIABLE,
UA_NODEID_NUMERIC(ns[1], 6005),
UA_NODEID_NUMERIC(ns[1], 5002),
UA_NODEID_NUMERIC(ns[0], 47),
UA_QUALIFIEDNAME(ns[1], "Va1"),
UA_NODEID_NUMERIC(ns[0], 63),
(const UA_NodeAttributes*)&attr, &UA_TYPES[UA_TYPES_VARIABLEATTRIBUTES],NULL, NULL);
UA_Double_delete(variablenode_ns_1_i_6005_variant_DataContents);
return retVal;
}

static UA_StatusCode function_testNS_21_finish(UA_Server *server, UA_UInt16* ns) {
return UA_Server_addNode_finish(server, 
UA_NODEID_NUMERIC(ns[1], 6005)
);
}

/* Va3 - ns=1;i=6007 */

static UA_StatusCode function_testNS_22_begin(UA_Server *server, UA_UInt16* ns) {
UA_StatusCode retVal = UA_STATUSCODE_GOOD;
UA_VariableAttributes attr = UA_VariableAttributes_default;
attr.minimumSamplingInterval = 0.000000;
attr.userAccessLevel = 1;
attr.accessLevel = 3;
/* Value rank inherited */
attr.valueRank = -1;
attr.dataType = UA_NODEID_NUMERIC(ns[0], 11);
UA_Double *variablenode_ns_1_i_6007_variant_DataContents =  UA_Double_new();
if (!variablenode_ns_1_i_6007_variant_DataContents) return UA_STATUSCODE_BADOUTOFMEMORY;
UA_Double_init(variablenode_ns_1_i_6007_variant_DataContents);
*variablenode_ns_1_i_6007_variant_DataContents = (UA_Double) 21.4;
UA_Variant_setScalar(&attr.value, variablenode_ns_1_i_6007_variant_DataContents, &UA_TYPES[UA_TYPES_DOUBLE]);
attr.displayName = UA_LOCALIZEDTEXT("", "Va3");
retVal |= UA_Server_addNode_begin(server, UA_NODECLASS_VARIABLE,
UA_NODEID_NUMERIC(ns[1], 6007),
UA_NODEID_NUMERIC(ns[1], 5002),
UA_NODEID_NUMERIC(ns[0], 47),
UA_QUALIFIEDNAME(ns[1], "Va3"),
UA_NODEID_NUMERIC(ns[0], 63),
(const UA_NodeAttributes*)&attr, &UA_TYPES[UA_TYPES_VARIABLEATTRIBUTES],NULL, NULL);
UA_Double_delete(variablenode_ns_1_i_6007_variant_DataContents);
return retVal;
}

static UA_StatusCode function_testNS_22_finish(UA_Server *server, UA_UInt16* ns) {
return UA_Server_addNode_finish(server, 
UA_NODEID_NUMERIC(ns[1], 6007)
);
}

/* Va2 - ns=1;i=6006 */

static UA_StatusCode function_testNS_23_begin(UA_Server *server, UA_UInt16* ns) {
UA_StatusCode retVal = UA_STATUSCODE_GOOD;
UA_VariableAttributes attr = UA_VariableAttributes_default;
attr.minimumSamplingInterval = 0.000000;
attr.userAccessLevel = 1;
attr.accessLevel = 3;
/* Value rank inherited */
attr.valueRank = -1;
attr.dataType = UA_NODEID_NUMERIC(ns[0], 11);
UA_Double *variablenode_ns_1_i_6006_variant_DataContents =  UA_Double_new();
if (!variablenode_ns_1_i_6006_variant_DataContents) return UA_STATUSCODE_BADOUTOFMEMORY;
UA_Double_init(variablenode_ns_1_i_6006_variant_DataContents);
*variablenode_ns_1_i_6006_variant_DataContents = (UA_Double) 13.7;
UA_Variant_setScalar(&attr.value, variablenode_ns_1_i_6006_variant_DataContents, &UA_TYPES[UA_TYPES_DOUBLE]);
attr.displayName = UA_LOCALIZEDTEXT("", "Va2");
retVal |= UA_Server_addNode_begin(server, UA_NODECLASS_VARIABLE,
UA_NODEID_NUMERIC(ns[1], 6006),
UA_NODEID_NUMERIC(ns[1], 5002),
UA_NODEID_NUMERIC(ns[0], 47),
UA_QUALIFIEDNAME(ns[1], "Va2"),
UA_NODEID_NUMERIC(ns[0], 63),
(const UA_NodeAttributes*)&attr, &UA_TYPES[UA_TYPES_VARIABLEATTRIBUTES],NULL, NULL);
UA_Double_delete(variablenode_ns_1_i_6006_variant_DataContents);
return retVal;
}

static UA_StatusCode function_testNS_23_finish(UA_Server *server, UA_UInt16* ns) {
return UA_Server_addNode_finish(server, 
UA_NODEID_NUMERIC(ns[1], 6006)
);
}

UA_StatusCode testNS(UA_Server *server) {
UA_StatusCode retVal = UA_STATUSCODE_GOOD;
/* Use namespace ids generated by the server */
UA_UInt16 ns[2];
ns[0] = UA_Server_addNamespace(server, "http://opcfoundation.org/UA/");
ns[1] = UA_Server_addNamespace(server, "http://yourorganisation.org/example/");
bool dummy = (
!(retVal = function_testNS_0_begin(server, ns))
&& !(retVal = function_testNS_1_begin(server, ns))
&& !(retVal = function_testNS_2_begin(server, ns))
&& !(retVal = function_testNS_3_begin(server, ns))
&& !(retVal = function_testNS_4_begin(server, ns))
&& !(retVal = function_testNS_5_begin(server, ns))
&& !(retVal = function_testNS_6_begin(server, ns))
&& !(retVal = function_testNS_7_begin(server, ns))
&& !(retVal = function_testNS_8_begin(server, ns))
&& !(retVal = function_testNS_9_begin(server, ns))
&& !(retVal = function_testNS_10_begin(server, ns))
&& !(retVal = function_testNS_11_begin(server, ns))
&& !(retVal = function_testNS_12_begin(server, ns))
&& !(retVal = function_testNS_13_begin(server, ns))
&& !(retVal = function_testNS_14_begin(server, ns))
&& !(retVal = function_testNS_15_begin(server, ns))
&& !(retVal = function_testNS_16_begin(server, ns))
&& !(retVal = function_testNS_17_begin(server, ns))
&& !(retVal = function_testNS_18_begin(server, ns))
&& !(retVal = function_testNS_19_begin(server, ns))
&& !(retVal = function_testNS_20_begin(server, ns))
&& !(retVal = function_testNS_21_begin(server, ns))
&& !(retVal = function_testNS_22_begin(server, ns))
&& !(retVal = function_testNS_23_begin(server, ns))
&& !(retVal = function_testNS_23_finish(server, ns))
&& !(retVal = function_testNS_22_finish(server, ns))
&& !(retVal = function_testNS_21_finish(server, ns))
&& !(retVal = function_testNS_20_finish(server, ns))
&& !(retVal = function_testNS_19_finish(server, ns))
&& !(retVal = function_testNS_18_finish(server, ns))
&& !(retVal = function_testNS_17_finish(server, ns))
&& !(retVal = function_testNS_16_finish(server, ns))
&& !(retVal = function_testNS_15_finish(server, ns))
&& !(retVal = function_testNS_14_finish(server, ns))
&& !(retVal = function_testNS_13_finish(server, ns))
&& !(retVal = function_testNS_12_finish(server, ns))
&& !(retVal = function_testNS_11_finish(server, ns))
&& !(retVal = function_testNS_10_finish(server, ns))
&& !(retVal = function_testNS_9_finish(server, ns))
&& !(retVal = function_testNS_8_finish(server, ns))
&& !(retVal = function_testNS_7_finish(server, ns))
&& !(retVal = function_testNS_6_finish(server, ns))
&& !(retVal = function_testNS_5_finish(server, ns))
&& !(retVal = function_testNS_4_finish(server, ns))
&& !(retVal = function_testNS_3_finish(server, ns))
&& !(retVal = function_testNS_2_finish(server, ns))
&& !(retVal = function_testNS_1_finish(server, ns))
&& !(retVal = function_testNS_0_finish(server, ns))
); (void)(dummy);
return retVal;
}
