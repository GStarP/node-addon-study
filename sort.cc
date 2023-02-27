#include <napi.h>

// sort impl
Napi::Value Sort(const Napi::CallbackInfo &info)
{
    // get env
    Napi::Env env = info.Env();
    // Napi::Value => Napi::Array
    const Napi::Array arr = info[0].As<Napi::Array>();
    unsigned int length = arr.Length();
    // Napi::Array => unsigned int[]
    unsigned int *nativeArr = new unsigned int[length];
    for (unsigned int i = 0; i < length; ++i)
    {
        nativeArr[i] = arr[i].As<Napi::Number>().Uint32Value();
    }
    // bubble sort
    for (unsigned int i = length - 1; i > 0; --i)
    {
        for (unsigned int j = 0; j < i; ++j)
        {
            if (nativeArr[j] > nativeArr[j + 1])
            {
                unsigned int tmp = nativeArr[j];
                nativeArr[j] = nativeArr[j + 1];
                nativeArr[j + 1] = tmp;
            }
        }
    }
    // return nativeArr
    Napi::Array retArr = Napi::Array::New(env, length);
    for (unsigned int i = 0; i < length; ++i)
    {
        retArr[i] = Napi::Number::New(env, double(nativeArr[i]));
    }
    // clean memory
    delete nativeArr;
    return retArr;
}

// declare export items
Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    exports.Set(Napi::String::New(env, "sort"), Napi::Function::New(env, Sort));
    return exports;
}
NODE_API_MODULE(sort, Init)