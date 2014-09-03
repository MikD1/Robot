using System;
using System.IO.Ports;

namespace Core
{
    internal class Robot : IRobot
    {
        public event Action Connected;
        public event Action Disconnected;

        public bool IsConnected
        {
            get
            {
                if (_port != null)
                {
                    return _port.IsOpen;
                }

                return false;
            }
        }

        public void Connect(string port, int speed)
        {
            OpenPort(port, speed);
        }

        public void Drive(DriveMode mode)
        {
            switch (mode.Direction)
            {
                case DriveDirection.Forward:
                    ExecuteCommand(0x22, 255);
                    break;

                case DriveDirection.Back:
                    ExecuteCommand(0x22, 252);
                    break;

                case DriveDirection.CW:
                    ExecuteCommand(0x22, 253);
                    break;

                case DriveDirection.CCW:
                    ExecuteCommand(0x22, 254);
                    break;
            }
        }
        public void Stop()
        {
            ExecuteCommand(0x22, 0);
        }

        public void Dispose()
        {
            if (_port != null && _port.IsOpen)
            {
                _port.Close();
                Utils.CallEvent(Disconnected);
            }
        }

        private void OpenPort(string port, int speed)
        {
            if (_port != null && _port.IsOpen)
            {
                _port.Close();
                Utils.CallEvent(Disconnected);
            }

            _port = new SerialPort(port, speed);
            _port.Open();
            Utils.CallEvent(Connected);
        }

        private void ExecuteCommand(byte command, byte argument)
        {
            byte[] bytes = new byte[] { command, argument };
            _port.Write(bytes, 0, 2);
        }

        private SerialPort _port;
    }
}
