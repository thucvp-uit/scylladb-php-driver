/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 455f26b7b90f46168ed0d35220853f8745bb521e */

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Cassandra_Date___construct, 0, 0, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Cassandra_Date_fromDateTime, 0, 1, Cassandra\\Date, 0)
	ZEND_ARG_OBJ_INFO(0, datetime, DateTimeInterface, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Cassandra_Date_toDateTime, 0, 0, DateTime, 0)
	ZEND_ARG_OBJ_INFO(0, time, Cassandra\\Time, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Cassandra_Date_seconds, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Cassandra_Date_type, 0, 0, Cassandra\\Type\\Scalar, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Cassandra_Date___toString, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()


ZEND_METHOD(Cassandra_Date, __construct);
ZEND_METHOD(Cassandra_Date, fromDateTime);
ZEND_METHOD(Cassandra_Date, toDateTime);
ZEND_METHOD(Cassandra_Date, seconds);
ZEND_METHOD(Cassandra_Date, type);
ZEND_METHOD(Cassandra_Date, __toString);


static const zend_function_entry class_Cassandra_Date_methods[] = {
	ZEND_ME(Cassandra_Date, __construct, arginfo_class_Cassandra_Date___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(Cassandra_Date, fromDateTime, arginfo_class_Cassandra_Date_fromDateTime, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Cassandra_Date, toDateTime, arginfo_class_Cassandra_Date_toDateTime, ZEND_ACC_PUBLIC)
	ZEND_ME(Cassandra_Date, seconds, arginfo_class_Cassandra_Date_seconds, ZEND_ACC_PUBLIC)
	ZEND_ME(Cassandra_Date, type, arginfo_class_Cassandra_Date_type, ZEND_ACC_PUBLIC)
	ZEND_ME(Cassandra_Date, __toString, arginfo_class_Cassandra_Date___toString, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static zend_class_entry *register_class_Cassandra_Date(zend_class_entry *class_entry_Cassandra_Value)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Cassandra", "Date", class_Cassandra_Date_methods);
	class_entry = zend_register_internal_class_ex(&ce, NULL);
	class_entry->ce_flags |= ZEND_ACC_FINAL|ZEND_ACC_NO_DYNAMIC_PROPERTIES;
	zend_class_implements(class_entry, 1, class_entry_Cassandra_Value);

	return class_entry;
}
