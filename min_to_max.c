#include <limits.h>
#include <stdio.h>
#include <postgres.h>
#include <fmgr.h>
#include <utils/array.h>
#include <catalog/pg_type.h>

PG_MODULE_MAGIC;

Datum min_max_val(PG_FUNCTION_ARGS);
PG_FUNCTION_INFO_V1(min_max_val);


Datum
min_max_val(PG_FUNCTION_ARGS)
{
  
  ArrayType *vals;

  
  Oid valueType;

  // The array element type widths for our input array:
  int valueTypeWidth;
  int returnTypeWidth;

  // The array element type "is passed by value" flags:
  bool valueTypeByValue;
  bool returnTypeByValue;

  // The array element type alignment codes:
  char valsTypeAlignmentCode;
  char retTypeAlignmentCode;

  // The array contents, as PostgreSQL "Datum" objects:
  Datum *valueContent;
  Datum returnContent[2];
  bool returnNulls[2] = {true, true};

  // List of "is null" flags for the array contents:
  bool *valueNullFlags;

  // The size of the input array:
  int valueLength;

  // The output array:
  ArrayType* returnArray;

  bool resultIsNull = true;
  int i;
  pgnum minV, maxV;
  int dims[1];
  int lbs[1];     // Lower Bounds of each dimension

  vals = PG_GETARG_ARRAYTYPE_P(0);

  
  // Determine the array element types.
  valueType = ARR_ELEMTYPE(vals);

  if (valueType != INT2OID &&
      valueType != INT4OID &&
      valueType != INT8OID &&
      valueType != FLOAT4OID &&
      valueType != FLOAT8OID) {
    ereport(ERROR, (errmsg("Input values  must be SMALLINT, INTEGER, BIGINT, REAL, or DOUBLE ")));
  }

  valueLength = (ARR_DIMS(vals))[0];

  get_typlenbyvalalign(valueType, &valueTypeWidth, &valueTypeByValue, &valsTypeAlignmentCode);

  // Extract the array contents (as Datum objects).
  deconstruct_array(vals, valueType, valueTypeWidth, valueTypeByValue, valsTypeAlignmentCode,
&valueContent, &valueNullFlags, &valueLength);

  if (valueLength == 0) PG_RETURN_NULL();

  // Compute the max.

  switch (valueType) {
    case INT2OID:
      for (i = 0; i < valueLength; i++) {
        if (valueNullFlags[i]) {
          continue;
        } else if (resultIsNull) {
          minV.i16 = DatumGetInt16(valueContent[i]);
          maxV.i16 = DatumGetInt16(valueContent[i]);
          resultIsNull = false;
        } else {
          if (DatumGetInt16(valueContent[i]) < minV.i16) minV.i16 = DatumGetInt16(valueContent[i]);
          if (DatumGetInt16(valueContent[i]) > maxV.i16) maxV.i16 = DatumGetInt16(valueContent[i]);
        }
      }
      returnContent[0] = Int16GetDatum(minV.i16);
      returnContent[1] = Int16GetDatum(maxV.i16);
      get_typlenbyvalalign(INT2OID, &returnTypeWidth, &returnTypeByValue, &retTypeAlignmentCode);
      break;
    case INT4OID:
      for (i = 0; i < valueLength; i++) {
        if (valueNullFlags[i]) {
          continue;
        } else if (resultIsNull) {
          minV.i32 = DatumGetInt32(valueContent[i]);
          maxV.i32 = DatumGetInt32(valueContent[i]);
          resultIsNull = false;
        } else {
          if (DatumGetInt32(valueContent[i]) < minV.i32) minV.i32 = DatumGetInt32(valueContent[i]);
          if (DatumGetInt32(valueContent[i]) > maxV.i32) maxV.i32 = DatumGetInt32(valueContent[i]);
        }
      }
      returnContent[0] = Int32GetDatum(minV.i32);
      returnContent[1] = Int32GetDatum(maxV.i32);
      get_typlenbyvalalign(INT4OID, &returnTypeWidth, &returnTypeByValue, &retTypeAlignmentCode);
      break;
    case INT8OID:
      for (i = 0; i < valueLength; i++) {
        if (valueNullFlags[i]) {
          continue;
        } else if (resultIsNull) {
          minV.i64 = DatumGetInt64(valueContent[i]);
          maxV.i64 = DatumGetInt64(valueContent[i]);
          resultIsNull = false;
        } else {
          if (DatumGetInt64(valueContent[i]) < minV.i64) minV.i64 = DatumGetInt64(valueContent[i]);
          if (DatumGetInt64(valueContent[i]) > maxV.i64) maxV.i64 = DatumGetInt64(valueContent[i]);
        }
      }
      returnContent[0] = Int64GetDatum(minV.i64);
      returnContent[1] = Int64GetDatum(maxV.i64);
      get_typlenbyvalalign(INT8OID, &returnTypeWidth, &returnTypeByValue, &retTypeAlignmentCode);
      break;
    case FLOAT4OID:
      for (i = 0; i < valueLength; i++) {
        if (valueNullFlags[i]) {
          continue;
        } else if (resultIsNull) {
          minV.f4 = DatumGetFloat4(valueContent[i]);
          maxV.f4 = DatumGetFloat4(valueContent[i]);
          resultIsNull = false;
        } else {
          if (DatumGetFloat4(valueContent[i]) < minV.f4) minV.f4 = DatumGetFloat4(valueContent[i]);
          if (DatumGetFloat4(valueContent[i]) > maxV.f4) maxV.f4 = DatumGetFloat4(valueContent[i]);
        }
      }
      returnContent[0] = Float4GetDatum(minV.f4);
      returnContent[1] = Float4GetDatum(maxV.f4);
      get_typlenbyvalalign(FLOAT4OID, &returnTypeWidth, &returnTypeByValue, &retTypeAlignmentCode);
      break;
    case FLOAT8OID:
      for (i = 0; i < valueLength; i++) {
        if (valueNullFlags[i]) {
          continue;
        } else if (resultIsNull) {
          minV.f8 = DatumGetFloat8(valueContent[i]);
          maxV.f8 = DatumGetFloat8(valueContent[i]);
          resultIsNull = false;
        } else {
          if (DatumGetFloat8(valueContent[i]) < minV.f8) minV.f8 = DatumGetFloat8(valueContent[i]);
          if (DatumGetFloat8(valueContent[i]) > maxV.f8) maxV.f8 = DatumGetFloat8(valueContent[i]);
        }
      }
      returnContent[0] = Float8GetDatum(minV.f8);
      returnContent[1] = Float8GetDatum(maxV.f8);
      get_typlenbyvalalign(FLOAT8OID, &returnTypeWidth, &returnTypeByValue, &retTypeAlignmentCode);
      break;
    default:
      ereport(ERROR, (errmsg("Input values must be SMALLINT, INTEGER, BIGINT, REAL, or DOUBLE ")));
  }

  lbs[0] = 1;
  dims[0] = 2;
  if (!resultIsNull) {
    returnNulls[0] = false;
    returnNulls[1] = false;
  }
  returnArray = construct_md_array(returnContent, returnNulls, 1, dims, lbs, valueType, returnTypeWidth, returnTypeByValue, retTypeAlignmentCode);

  PG_RETURN_ARRAYTYPE_P(returnArray);
}
