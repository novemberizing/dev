import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import React from 'react';
import Page from '../../component/ui/page';
import Reacts from '../../util/reacts';

import DashboardCard from '../../component/ui/card/dashboard';
import DashboardProgressCard from '../../component/ui/card/dashboard/progress';
import DefaultCard from '../../component/ui/card/default';
import DropdownCard from '../../component/ui/card/dropdown';
import CollapseCard from '../../component/ui/card/collapse';

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
                    <DashboardCard shadow={true} icon={["fas", "calendar"]} type="primary" border="left" xl={3} md={6} py={2} height={100} title="Earnings (Monthly)">
                        $40,000
                    </DashboardCard>
                    <DashboardCard shadow={true} icon={["fas", "dollar-sign"]} type="success" border="left" xl={3} md={6} py={2} height={100} title="Earnings (Annual)">
                        $215,000
                    </DashboardCard>
                    <DashboardProgressCard shadow={true} icon={["fas", "clipboard-list"]} type="info" border="left" xl={3} md={6} py={2} height={100} title="Tasks">
                        50%
                    </DashboardProgressCard>
                    <DashboardCard shadow={true} icon={["fas", "comments"]} type="warning" border="left" xl={3} md={6} py={2} height={100} title="Pending Requests">
                        18
                    </DashboardCard>
                </Page.Row>
                <Page.Row>
                    <Page.Column lg={6}>
                        <DefaultCard mb={4} title="Default Card Example">
                            This card uses Bootstrap's default styling with no utility classes added. Global styles are the only things modifying the look and feel of this default card example.
                        </DefaultCard>
                        <DefaultCard mb={4} title="Basic Card Example" type="primary" shadow={true}>
                            The styling for this basic card example is created by using default Bootstrap utility classes. By using utility classes, the style of the card component can be easily modified with no need for any custom CSS!
                        </DefaultCard>
                    </Page.Column>
                    <Page.Column lg={6}>
                        <DropdownCard mb={4} menu="dropdown menu" title="Dropdown Card Example" type="primary" shadow={true}>
                            <DropdownCard.Menu>
                                <DropdownCard.Menu.Header name="Dropdown Menu" />
                                <DropdownCard.Menu.Item href="#" name="Action" />
                                <DropdownCard.Menu.Item href="#" name="Another action" />
                                <DropdownCard.Menu.Divider />
                                <DropdownCard.Menu.Item href="#" name="Something else here" />
                            </DropdownCard.Menu>
                            Dropdown menus can be placed in the card header in order to extend the functionality of a basic card. In this dropdown card example, the Font Awesome vertical ellipsis icon in the card header can be clicked on in order to toggle a dropdown menu.
                        </DropdownCard>
                        <CollapseCard mb={4} menu="dropdown menu" title="Dropdown Card Example" type="primary" shadow={true}>
                            This is a collapsable card example using Bootstrap's built in collapse functionality. <strong>Click on the card header</strong> to see the card body collapse and expand!
                        </CollapseCard>
                    </Page.Column>
                </Page.Row>
            </div>
        );
    }
}