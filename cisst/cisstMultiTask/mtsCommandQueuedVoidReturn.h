/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-    */
/* ex: set filetype=cpp softtabstop=4 shiftwidth=4 tabstop=4 cindent expandtab: */

/*
  $Id$

  Author(s): Anton Deguet
  Created on: 2010-09-16

  (C) Copyright 2010-2014 Johns Hopkins University (JHU), All Rights Reserved.

--- begin cisst license - do not edit ---

This software is provided "as is" under an open source license, with
no warranty.  The complete license can be found in license.txt and
http://www.cisst.org/cisst/license.txt.

--- end cisst license ---
*/


/*!
  \file
  \brief Define an internal command for cisstMultiTask
*/


#ifndef _mtsCommandQueuedVoidReturn_h
#define _mtsCommandQueuedVoidReturn_h

#include <cisstMultiTask/mtsCommandVoidReturn.h>
#include <cisstMultiTask/mtsCommandRead.h>
#include <cisstMultiTask/mtsCallableReadBase.h>
#include <cisstMultiTask/mtsQueue.h>

// Always include last
#include <cisstMultiTask/mtsExport.h>

class mtsCommandWriteBase;

/*!
  \ingroup cisstMultiTask

 */

template <class _Base>
class mtsCommandQueuedVoidReturnBase: public _Base
{
public:
    typedef _Base BaseType;

    /*! This type. */
    typedef mtsCommandQueuedVoidReturnBase<_Base> ThisType;

    typedef typename _Base::CallableType CallableType;

protected:
    /*! Mailbox used to queue the commands */
    mtsMailBox * MailBox;

    size_t ArgumentQueueSize; // size used for queues

    /*! Queue to store pointer to return value */
    mtsQueue<mtsGenericObject *> ReturnsQueue;

    /*! Queue for return events (to send result to caller) */
    mtsQueue<mtsCommandWriteBase *> FinishedEventQueue;

private:
    /*! Private default constructor to prevent use. */
    mtsCommandQueuedVoidReturnBase(void);

    /*! Private copy constructor to prevent copies */
    mtsCommandQueuedVoidReturnBase(const ThisType & CMN_UNUSED(other));

public:

    mtsCommandQueuedVoidReturnBase(CallableType * callable, const std::string & name,
                                   const mtsGenericObject * resultPrototype,
                                   mtsMailBox * mailBox, size_t size);

    /*! Destructor */
    virtual ~mtsCommandQueuedVoidReturnBase();

    virtual std::string GetClassName(void) const;

    virtual ThisType * Clone(mtsMailBox * mailBox, size_t size) const;

    // virtual method defined in base class
    mtsExecutionResult Execute(mtsGenericObject & result);

    // virtual method defined in this class
    virtual mtsExecutionResult Execute(mtsGenericObject & result,
                                       mtsCommandWriteBase * finishedEventHandler);

    std::string GetMailBoxName(void) const;

    inline virtual mtsGenericObject * ReturnGet(void) {
        return *(ReturnsQueue.Get());
    }

    inline virtual mtsCommandWriteBase * FinishedEventGet(void) {
        return *(FinishedEventQueue.Get());
    }

    void ToStream(std::ostream & outputStream) const;
};

typedef mtsCommandQueuedVoidReturnBase<mtsCommandVoidReturn> mtsCommandQueuedVoidReturn;
typedef mtsCommandQueuedVoidReturnBase<mtsCommandRead> mtsCommandQueuedRead;

#ifdef CISST_COMPILER_IS_MSVC
#pragma warning ( disable : 4661 )
template class CISST_EXPORT mtsCommandQueuedVoidReturnBase<mtsCommandVoidReturn>;
template class CISST_EXPORT mtsCommandQueuedVoidReturnBase<mtsCommandRead>;
#endif

#endif // _mtsCommandQueuedVoidReturn_h

