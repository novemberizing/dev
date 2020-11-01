import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import React from 'react';
import Page from '../../component/ui/page';
import Reacts from '../../util/reacts';

import DashboardCard from '../../component/ui/card/dashboard';
import DashboardProgressCard from '../../component/ui/card/dashboard/progress';
import DefaultCard from '../../component/ui/card/default';
import DropdownCard from '../../component/ui/card/dropdown';
import CollapseCard from '../../component/ui/card/collapse';
import CircleBtn from '../../component/ui/button/circle';
import SplitBtn from '../../component/ui/button/split';
import BrandBtn from '../../component/ui/button/brand';

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
                        <DefaultCard mb={4} title="Circle Buttons" type="primary" shadow={true}>
                            <p>Use Font Awesome Icons (included with this theme package) along with the circle buttons as shown in the examples below!</p>
                            <div className="mb-2">
                                <code>.btn-circle</code>
                            </div>
                            <CircleBtn href="#" icon={["fab", "facebook-f"]} type="primary" />
                            <CircleBtn href="#" icon={["fas", "check"]} type="success" />
                            <CircleBtn href="#" icon={["fas", "info-circle"]} type="info" />
                            <CircleBtn href="#" icon={["fas", "exclamation-triangle"]} type="warning" />
                            <CircleBtn href="#" icon={["fas", "trash"]} type="danger" />
                            <div className="mt-4 mb-2">
                                <code>.btn-circle .btn-sm</code>
                            </div>
                            <CircleBtn href="#" icon={["fab", "facebook-f"]} type="primary" size="sm" />
                            <CircleBtn href="#" icon={["fas", "check"]} type="success" size="sm" />
                            <CircleBtn href="#" icon={["fas", "info-circle"]} type="info" size="sm" />
                            <CircleBtn href="#" icon={["fas", "exclamation-triangle"]} type="warning" size="sm" />
                            <CircleBtn href="#" icon={["fas", "trash"]} type="danger" size="sm" />
                            <div className="mt-4 mb-2">
                                <code>.btn-circle .btn-lg</code>
                            </div>
                            <CircleBtn href="#" icon={["fab", "facebook-f"]} type="primary" size="lg" />
                            <CircleBtn href="#" icon={["fas", "check"]} type="success" size="lg" />
                            <CircleBtn href="#" icon={["fas", "info-circle"]} type="info" size="lg" />
                            <CircleBtn href="#" icon={["fas", "exclamation-triangle"]} type="warning" size="lg" />
                            <CircleBtn href="#" icon={["fas", "trash"]} type="danger" size="lg" />
                        </DefaultCard>
                        <DefaultCard mb={4} title="Bland Buttons" type="primary" shadow={true}>
                            <p>Google and Facebook buttons are available featuring each company's respective brand color. They are used on the user login and registration pages.</p>
                            <p>You can create more custom buttons by adding a new color variable in the <code>_variables.scss</code> file and then using the Bootstrap button variant mixin to create a new style, as demonstrated in the <code>_buttons.scss</code> file.</p>
                            <BrandBtn href="#" brand="google">GOOGLE</BrandBtn>
                            <BrandBtn href="#" brand="facebook">FAEBOOK</BrandBtn>
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
                        <DefaultCard mb={4} title="Split Buttons with Icon" type="primary" shadow={true}>
                            <p>Works with any button colors, just use the <code>.btn-icon-split</code> class and the markup in the examples below. The examples below also use the <code>.text-white-50</code> helper class on the icons for additional styling, but it is not required.</p>
                            <SplitBtn href="#" icon={["fas", "flag"]} type="primary">Split Button Primary</SplitBtn>
                            <div className="my-2"></div>
                            <SplitBtn href="#" icon={["fas", "check"]} type="success">Split Button Success</SplitBtn>
                            <div className="my-2"></div>
                            <SplitBtn href="#" icon={["fas", "info-circle"]} type="info">Split Button Info</SplitBtn>
                            <div className="my-2"></div>
                            <SplitBtn href="#" icon={["fas", "exclamation-triangle"]} type="warning">Split Button Warning</SplitBtn>
                            <div className="my-2"></div>
                            <SplitBtn href="#" icon={["fas", "trash"]} type="danger">Split Button Danger</SplitBtn>
                            <div className="my-2"></div>
                            <SplitBtn href="#" icon={["fas", "arrow-right"]} type="secondary">Split Button Secondary</SplitBtn>
                            <div className="my-2"></div>
                            <SplitBtn href="#" icon={["fas", "arrow-right"]} type="light">Split Button Light</SplitBtn>
                            <div className="my-2"></div>
                            <p>Also works with small and large button classes!</p>
                            <SplitBtn href="#" icon={["fas", "flag"]} type="primary" size="sm">Split Button Small</SplitBtn>
                            <div className="my-2"></div>
                            <SplitBtn href="#" icon={["fas", "flag"]} type="primary" size="lg">Split Button Large</SplitBtn>
                            <div className="my-2"></div>
                        </DefaultCard>
                    </Page.Column>
                </Page.Row>
            </div>
        );
    }
}