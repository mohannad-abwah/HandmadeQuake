#pragma once

int32 Q_strcmp(const uchar* s1, const uchar* s2);
int32 Q_atoi(const uchar* str);
void Q_strcpy(uchar* dest, const uchar* src);
void Q_strncpy(uchar* dest, const uchar* src, size_t n);
size_t Q_strlen(const uchar* src);