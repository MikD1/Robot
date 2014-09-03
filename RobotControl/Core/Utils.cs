using System;

namespace Core
{
    public static class Utils
    {
        public static void CallEvent(Action act)
        {
            if (act != null)
            {
                act();
            }
        }
        public static void CallEvent<T>(Action<T> act, T arg1)
        {
            if (act != null)
            {
                act(arg1);
            }
        }
    }
}
