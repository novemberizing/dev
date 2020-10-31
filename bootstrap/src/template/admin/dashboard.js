import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import React from 'react';
import Page from '../../component/ui/page';
import Reacts from '../../util/reacts';

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
                <Page.Row />
            </div>
        );
    }
}