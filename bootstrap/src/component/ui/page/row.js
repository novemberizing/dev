import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import React from 'react';
import Card from '../card';
import DashboardCard from '../card/dashboard';
import DashboardProgressCard from '../card/dashboard/progress';

export default class PageRow extends React.Component {
    render() {
        return (
            <div className="row">
                <DashboardCard icon={["fas", "calendar"]} type="primary" border="left" xl={3} md={6} py={2} height={100} title="Earnings (Monthly)">
                    $40,000
                </DashboardCard>
                <DashboardCard icon={["fas", "dollar-sign"]} type="success" border="left" xl={3} md={6} py={2} height={100} title="Earnings (Annual)">
                    $215,000
                </DashboardCard>
                <DashboardProgressCard icon={["fas", "clipboard-list"]} type="info" border="left" xl={3} md={6} py={2} height={100} title="Tasks">
                    50%
                </DashboardProgressCard>
                <DashboardCard icon={["fas", "comments"]} type="warning" border="left" xl={3} md={6} py={2} height={100} title="Pending Requests">
                    18
                </DashboardCard>
          </div>
        );
    }
}