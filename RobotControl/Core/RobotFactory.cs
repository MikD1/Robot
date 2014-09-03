using System;

namespace Core
{
    public static class RobotFactory
    {
        public static IRobot GetRobot()
        {
            if (_robot == null)
            {
                _robot = new Robot();
            }

            return _robot;
        }

        private static IRobot _robot;
    }
}
