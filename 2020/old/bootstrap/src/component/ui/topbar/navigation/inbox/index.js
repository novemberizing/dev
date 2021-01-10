import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import React from 'react';
import TopbarNavDropdown from '../dropdown';
import TopbarNavInboxItem from './item';
import Reacts from '../../../../../util/reacts';
import person from '../../../../../template/res/image/example/person.jpg';
import Strings from '../../../../../util/strings';

const __example = [
    { image: person, alt: "alt", status: "primary", bold: true, message: "Hi there! I am wondering if you can help me with a problem I've been having.", from: "Emily Fowler", time: "58m" },
    { image: person, alt: "alt", bold: false, message: "I have the photos that you ordered last month, how would you like them sent to you?", from: "Jae Chun", time: "1d" },
    { image: person, alt: "alt", status: "success", bold: false, status: "warning", message: "Last month's report looks great, I am very happy with the progress so far, keep up the good work!", from: "Morgan Alvarez", time: "2d" },
    { image: person, alt: "alt", status: "warning", bold: false, status: "success", message: "Am I a good boy? The reason I ask is because someone told me that people say this to all dogs, even if they aren't good...", from: "Chicken the Dog", time: "2w" }
];

export default class TopbarNavInbox extends TopbarNavDropdown {
    constructor(props) {
        super(props);

        this.state = {
            messages: __example
        };
    }

    messages() {
        return this.state.messages.map((o, index) => {
            return (<TopbarNavInboxItem image={o.image} alt={o.alt} status={o.status} bold={o.bold} message={o.message} from={o.from} time={o.time} key={index} />);
        }).concat();
    }

    render() {
        return (
            <li className="nav-item dropdown no-arrow mx-1">
                <a className="nav-link dropdown-toggle" href="#" id="messagesDropdown" role="button" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false" onClick={this.toggle}>
                    <FontAwesomeIcon icon={["fas", "envelope"]} fixedWidth size="1x" />
                    <span className="badge badge-danger badge-counter">7</span>
                </a>
                {Reacts.display(this.state.visible,
                    <div className="dropdown-list dropdown-menu dropdown-menu-right shadow animated--grow-in show" aria-labelledby="messagesDropdown">
                        <h6 className="dropdown-header">
                            Message Center
                        </h6>
                        {this.messages()}
                        <a className="dropdown-item text-center small text-gray-500" href="#">Read More Messages</a>
                    </div>
                )}
            </li>
        );
    }
}