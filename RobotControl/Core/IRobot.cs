using System;

namespace Core
{
    public interface IRobot : IDisposable
    {
        event Action Connected;
        event Action Disconnected;

        bool IsConnected { get; }

        void Connect(string port, int speed);
        
        void Drive(DriveMode mode);
        void Stop();
    }

    public enum DriveDirection
    {
        Forward, Back, CW, CCW
    }

    public struct DriveMode
    {
        public DriveDirection Direction { get; set; }
        public byte Speed { get; set; }
    }
}
