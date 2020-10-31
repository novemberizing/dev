import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import React from 'react';
import Reacts from '../../../../../util/reacts';
import TopbarNavDropdown from '../dropdown';
import TopbarNavAlarmItem from './item';

export default class TopbarNavAlarm extends TopbarNavDropdown {
    constructor(props) {
        super(props);
    }

    render() {
        return (
            <li className="nav-item dropdown no-arrow ">
                <a className="nav-link dropdown-toggle" href="#" onClick={this.toggle}>
                    <FontAwesomeIcon icon={["fas", "bell"]} fixedWidth size="1x" />
                    <span className="badge badge-danger badge-counter">3</span>
                </a>
                {Reacts.display(this.state.visible,
                    <div className="dropdown-list dropdown-menu dropdown-menu-right shadow animated--grow-in show" aria-labelledby="alertsDropdown">
                        <h6 className="dropdown-header">
                            Alerts Center
                        </h6>
                        <TopbarNavAlarmItem icon={["fas", "file-alt"]} type="primary" date="December 12, 2019" bold={true} message="A new monthly report is ready to download!" />
                        <TopbarNavAlarmItem icon={["fas", "donate"]} type="success" date="December 7, 2019" bold={false} message="$290.29 has been deposited into your account!" />
                        <TopbarNavAlarmItem icon={["fas", "exclamation-triangle"]} type="warning" date="December 2, 2019" bold={false} message="Spending Alert: We've noticed unusually high spending for your account." />
                        <a className="dropdown-item text-center small text-gray-500" href="#">Show All Alerts</a>
                    </div>
                )}
            </li>
        );
    }
}

TopbarNavAlarm.Item = TopbarNavAlarm;