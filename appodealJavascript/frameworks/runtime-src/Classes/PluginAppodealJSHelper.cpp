#include "PluginAppodealJSHelper.h"
#include "cocos2d_specifics.hpp"
#include "PluginAppodeal/PluginAppodeal.h"
#include "SDKBoxJSHelper.h"

extern JSObject* jsb_sdkbox_PluginAppodeal_prototype;
static JSContext* s_cx = nullptr;

class ADCallbackJS: public cocos2d::CCObject {
public:
    ADCallbackJS();
    void schedule();
    void notityJs(float dt);

    std::string _name;
    
    jsval _paramVal[2];
    int _paramLen;
};

class AppodealListenerJS : public sdkbox::AppodealListener {
private:
    JSObject* _JSDelegate;
public:
    void setJSDelegate(JSObject* delegate) {
        _JSDelegate = delegate;
    }

    JSObject* getJSDelegate() {
        return _JSDelegate;
    }

    void onBannerDidLoadAd() {
        ADCallbackJS* cb = new ADCallbackJS();
        cb->_name = "onBannerDidLoadAd";
        cb->schedule();
        cb->autorelease();
    }

    void onBannerDidFailToLoadAd() {
        ADCallbackJS* cb = new ADCallbackJS();
        cb->_name = "onBannerDidFailToLoadAd";
        cb->schedule();
        cb->autorelease();
    }

    void onBannerDidClick() {
        ADCallbackJS* cb = new ADCallbackJS();
        cb->_name = "onBannerDidClick";
        cb->schedule();
        cb->autorelease();
    }

    void onBannerPresent() {
        ADCallbackJS* cb = new ADCallbackJS();
        cb->_name = "onBannerPresent";
        cb->schedule();
        cb->autorelease();
    }

    void onInterstitialDidLoadAd() {
        ADCallbackJS* cb = new ADCallbackJS();
        cb->_name = "onInterstitialDidLoadAd";
        cb->schedule();
        cb->autorelease();
    }

    void onInterstitialDidFailToLoadAd() {
        ADCallbackJS* cb = new ADCallbackJS();
        cb->_name = "onInterstitialDidFailToLoadAd";
        cb->schedule();
        cb->autorelease();
    }

    void onInterstitialWillPresent() {
        ADCallbackJS* cb = new ADCallbackJS();
        cb->_name = "onInterstitialWillPresent";
        cb->schedule();
        cb->autorelease();
    }

    void onInterstitialDidDismiss() {
        ADCallbackJS* cb = new ADCallbackJS();
        cb->_name = "onInterstitialDidDismiss";
        cb->schedule();
        cb->autorelease();
    }

    void onInterstitialDidClick() {
        ADCallbackJS* cb = new ADCallbackJS();
        cb->_name = "onInterstitialDidClick";
        cb->schedule();
        cb->autorelease();
    }

    void onVideoDidLoadAd() {
        ADCallbackJS* cb = new ADCallbackJS();
        cb->_name = "onVideoDidLoadAd";
        cb->schedule();
        cb->autorelease();
    }

    void onVideoDidFailToLoadAd() {
        ADCallbackJS* cb = new ADCallbackJS();
        cb->_name = "onVideoDidFailToLoadAd";
        cb->schedule();
        cb->autorelease();
    }

    void onVideoDidPresent() {
        ADCallbackJS* cb = new ADCallbackJS();
        cb->_name = "onVideoDidPresent";
        cb->schedule();
        cb->autorelease();
    }

    void onVideoWillDismiss() {
        ADCallbackJS* cb = new ADCallbackJS();
        cb->_name = "onVideoWillDismiss";
        cb->schedule();
        cb->autorelease();
    }

    void onVideoDidFinish() {
        ADCallbackJS* cb = new ADCallbackJS();
        cb->_name = "onVideoDidFinish";
        cb->schedule();
        cb->autorelease();
    }
    
    void onRewardVideoDidFinish(int amount, const std::string& name) {
        JSContext* cx = s_cx;

        ADCallbackJS* cb = new ADCallbackJS();
        cb->_name = "onRewardVideoDidFinish";
        cb->_paramVal[0] = INT_TO_JSVAL(amount);;
        cb->_paramVal[1] = std_string_to_jsval(cx, name);
        cb->_paramLen = 2;
        cb->schedule();
        cb->autorelease();
    }

    void invokeJS(const char* func, jsval* pVals, int valueSize) {
        if (!s_cx) {
            return;
        }
        JSContext* cx = s_cx;
        const char* func_name = func;
        JS::RootedObject obj(cx, _JSDelegate);
        JSAutoCompartment ac(cx, obj);

#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 33
        bool hasAction;
        JS::RootedValue retval(cx);
        JS::RootedValue func_handle(cx);
#else
        bool hasAction;
        jsval retval;
        JS::RootedValue func_handle(cx);
#endif
#elif defined(JS_VERSION)
        JSBool hasAction;
        jsval retval;
        jsval func_handle;
#endif

        if (JS_HasProperty(cx, obj, func_name, &hasAction) && hasAction) {
            if(!JS_GetProperty(cx, obj, func_name, &func_handle)) {
                return;
            }
            if(func_handle == JSVAL_VOID) {
                return;
            }

#if MOZJS_MAJOR_VERSION >= 31
            if (0 == valueSize) {
                JS_CallFunctionName(cx, obj, func_name, JS::HandleValueArray::empty(), &retval);
            } else {
                JS_CallFunctionName(cx, obj, func_name, JS::HandleValueArray::fromMarkedLocation(valueSize, pVals), &retval);
            }
#else
            if (0 == valueSize) {
                JS_CallFunctionName(cx, obj, func_name, 0, nullptr, &retval);
            } else {
                JS_CallFunctionName(cx, obj, func_name, valueSize, pVals, &retval);
            }
#endif
        }
    }

};

ADCallbackJS::ADCallbackJS():
_paramLen(0) {
}

void ADCallbackJS::schedule() {
    retain();
    cocos2d::CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(ADCallbackJS::notityJs), this, 0.1, false);
}

void ADCallbackJS::notityJs(float dt) {
    sdkbox::AppodealListener* lis = sdkbox::PluginAppodeal::getListener();
    AppodealListenerJS* l = dynamic_cast<AppodealListenerJS*>(lis);
    if (l) {
        l->invokeJS(_name.c_str(), _paramVal, _paramLen);
    }
    cocos2d::CCDirector::sharedDirector()->getScheduler()->unscheduleAllForTarget(this);
    release();
}


#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 33
bool js_PluginAppodealJS_PluginAppodeal_setListener(JSContext *cx, uint32_t argc, jsval *vp)
#else
bool js_PluginAppodealJS_PluginAppodeal_setListener(JSContext *cx, uint32_t argc, jsval *vp)
#endif
#elif defined(JS_VERSION)
JSBool js_PluginAppodealJS_PluginAppodeal_setListener(JSContext *cx, uint32_t argc, jsval *vp)
#endif
{
    s_cx = cx;
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;

    if (argc == 1) {

        if (!args.get(0).isObject())
        {
            ok = false;
        }
        JSObject *tmpObj = args.get(0).toObjectOrNull();

        JSB_PRECONDITION2(ok, cx, false, "js_PluginAppodealJS_PluginAppodeal_setIAPListener : Error processing arguments");
        AppodealListenerJS* wrapper = new AppodealListenerJS();
        wrapper->setJSDelegate(tmpObj);
        sdkbox::PluginAppodeal::setListener(wrapper);

        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_PluginAppodealJS_PluginAppodeal_setIAPListener : wrong number of arguments");
    return false;
}


#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 33
void register_all_PluginAppodealJS_helper(JSContext* cx, JS::HandleObject global) {
    JS::RootedObject pluginObj(cx);
    sdkbox::getJsObjOrCreat(cx, global, "sdkbox.PluginAppodeal", &pluginObj);

    JS_DefineFunction(cx, pluginObj, "setListener", js_PluginAppodealJS_PluginAppodeal_setListener, 1, JSPROP_READONLY | JSPROP_PERMANENT);
}
#else
void register_all_PluginAppodealJS_helper(JSContext* cx, JSObject* global) {
    JS::RootedObject pluginObj(cx);
    sdkbox::getJsObjOrCreat(cx, JS::RootedObject(cx, global), "sdkbox.PluginAppodeal", &pluginObj);

    JS_DefineFunction(cx, pluginObj, "setListener", js_PluginAppodealJS_PluginAppodeal_setListener, 1, JSPROP_READONLY | JSPROP_PERMANENT);
}
#endif
#elif defined(JS_VERSION)
void register_all_PluginAppodealJS_helper(JSContext* cx, JSObject* global) {
    jsval pluginVal;
    JSObject* pluginObj;
    pluginVal = sdkbox::getJsObjOrCreat(cx, global, "sdkbox.PluginAppodeal", &pluginObj);

    JS_DefineFunction(cx, pluginObj, "setListener", js_PluginAppodealJS_PluginAppodeal_setListener, 1, JSPROP_READONLY | JSPROP_PERMANENT);
}
#endif
