using Core;
using System;
using System.Threading;
using System.Windows;

namespace RobotControlPanel
{
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            _robot.Connected += RobotOnConnected;
            _robot.Disconnected += RobotOnDisconnected;
        }

        private void RobotOnConnected()
        {
            ConnectLabel.Text = "Connected";
            ConnectButton.IsEnabled = false;
        }
        private void RobotOnDisconnected()
        {
            ConnectLabel.Text = "Disconnected";
            ConnectButton.IsEnabled = true;
        }
        private void ConnectButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                _robot.Connect("com10", 9600);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
        private void Window_KeyDown(object sender, System.Windows.Input.KeyEventArgs e)
        {
            if (_robot.IsConnected)
            {
                switch (e.Key)
                {
                    case System.Windows.Input.Key.Up:
                        _robot.Drive(new DriveMode { Direction = DriveDirection.Forward, Speed = 1 });
                        break;

                    case System.Windows.Input.Key.Down:
                        _robot.Drive(new DriveMode { Direction = DriveDirection.Back, Speed = 1 });
                        break;

                    case System.Windows.Input.Key.Left:
                        _robot.Drive(new DriveMode { Direction = DriveDirection.CCW, Speed = 1 });
                        break;

                    case System.Windows.Input.Key.Right:
                        _robot.Drive(new DriveMode { Direction = DriveDirection.CW, Speed = 1 });
                        break;

                    case System.Windows.Input.Key.Space:
                        _robot.Shot();
                        break;
                }
            }
        }
        private void Window_KeyUp(object sender, System.Windows.Input.KeyEventArgs e)
        {
            if (_robot.IsConnected)
            {
                switch (e.Key)
                {
                    case System.Windows.Input.Key.Up:
                    case System.Windows.Input.Key.Down:
                    case System.Windows.Input.Key.Left:
                    case System.Windows.Input.Key.Right:
                        _robot.Stop();
                        break;
                }
            }
        }

        private readonly IRobot _robot = RobotFactory.GetRobot();
    }
}
