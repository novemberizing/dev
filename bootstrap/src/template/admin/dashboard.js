import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import React from 'react';
import Page from '../../component/ui/page';
import Reacts from '../../util/reacts';

import DashboardCard from '../../component/ui/card/dashboard';
import DashboardProgressCard from '../../component/ui/card/dashboard/progress';
import DefaultCard from '../../component/ui/card/default';

export default class TemplateAdminDashboard extends Page {
    constructor(props) {
        super(props);

        this.state = {
            title: 'Dashboard'
        };
    }

    render() {
        return (
            <div className="container-fluid">
                {Reacts.display(this.state.title,
                    <Page.Header title={this.state.title}>
                        <a href="#" className="d-none d-sm-inline-block btn btn-sm btn-primary shadow-sm">
                            <FontAwesomeIcon icon={["fas", "download"]} size="sm" className="text-white-50" /> Generate Report
                        </a>
                    </Page.Header>
                )}
                <Page.Row>
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
                </Page.Row>
                <Page.Row>
                    <Page.Column lg={6}>
                        <DefaultCard mb={4} title="Default Card Example">
                            This card uses Bootstrap's default styling with no utility classes added. Global styles are the only things modifying the look and feel of this default card example.
                        </DefaultCard>
                    </Page.Column>
                </Page.Row>
            </div>
        );
    }
}