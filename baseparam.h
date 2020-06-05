#ifndef BASEPARAM_H
#define BASEPARAM_H
#include <QThread>
#include <QDebug>
#include <QDateTime>
#include <QString>

#define OBJ_DEBUG qDebug()<<QThread::currentThreadId()<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz")<<__FILE__<<":"<<__FUNCTION__<<__LINE__<<":"
// 断言判断，判断指针是否为空，为空时返回入参value
#define ASSERT_POINT_RETURN(point,value)    if (point == nullptr) {\
                                                OBJ_DEBUG << point <<"ASSERT ERROR!";\
                                                return value;\
                                            }
// 断言判断，判断指针是否为空，为空时返回void
#define ASSERT_POINT_RETURN_VOID(point)     if (point == nullptr) {\
                                                OBJ_DEBUG << point << "ASSERT ERROR!";\
                                                return;\
                                            }
#define ASSERT_POINT_NOT_NULL(point)     (point != nullptr)

#define ASSERT_POINT_IS_NULL(point)     (point == nullptr)
#endif // BASEPARAM_H
