/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _UI_DISPLAY_DISPATCHER_H
#define _UI_DISPLAY_DISPATCHER_H

#include <ui/Input.h>
#include <ui/InputTransport.h>
#include <utils/KeyedVector.h>
#include <utils/Vector.h>
#include <utils/threads.h>
#include <utils/Timers.h>
#include <utils/RefBase.h>
#include <utils/String8.h>
#include <utils/Looper.h>
#include <utils/BitSet.h>
#include <ui/DisplaySemaphore.h>
#include <hardware/display.h>
#include <hardware/hardware.h>
#include <stddef.h>
#include <unistd.h>
#include <limits.h>

#define   DISPLAYDISPATCH_MAXBUFNO      3

namespace android 
{
    /* ͬ��ʱ��֡�����߳� */
    class DisplayDispatcherThread : public Thread 
    {
        public:
            explicit DisplayDispatcherThread(display_device_t*	mDevice);
            ~DisplayDispatcherThread();
            void                setSrcBuf(int srcfb_id,int srcfb_offset);
            void                signalEvent();
            void                waitForEvent();
            void 				resetEvent();

        private:
            sp<DisplaySemaphore>    mSemaphore;
            int                 mSrcfbid;
            int                 mSrcfboffset;
            int                 mCurfb;             /*����ͬ��ʱ��Ҫ��ʾ������Ҫ��ʾ��fb no*/
            int                 mFbOffset;          /*���嵱ǰ�ڸ�������ʾ��fb�е�buffer id*/
            int                 mFrameidx[DISPLAYDISPATCH_MAXBUFNO];  /*ÿ��buffer�����֡��*/
            void				enqueuebuf(int frameidx);
            virtual bool        threadLoop();
            void 				LooperOnce();
    		display_device_t*	mDispDevice;	
    };

    class DisplayDispatcher:public virtual RefBase
    {
        public:
            DisplayDispatcher();
            ~DisplayDispatcher();

            void startSwapBuffer();
        private:
            sp<DisplayDispatcherThread>   mThread;
            display_device_t*	mDevice;	
            
    };

} // namespace android

#endif // _UI_INPUT_DISPATCHER_H
