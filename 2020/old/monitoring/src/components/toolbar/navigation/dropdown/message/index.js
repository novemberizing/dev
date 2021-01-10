import React from "react";
import ToolbarNavDropdown from "..";
import ToolbarNavDropdownMessageItem from "./item";
import source from "../../../../../img/source.jpg";

// console.log(source);

export default class ToolbarNavDropdownMessage extends React.Component {
    constructor(props){
        super(props);


        this.state = {
            messages: [
                {
                    image: source,
                    alt: "alt",
                    status: "bg-success",
                    bold:true,
                    message: "Hi there! I am wondering if you can help me with a problem I've been having.",
                    from: "Emily Fowler",
                    when: "58m"
                },
                {
                    image: source,
                    alt: "alt",
                    status: "",
                    bold:false,
                    message: "I have the photos that you ordered last month, how would you like them sent to you?",
                    from: "Jae Chun",
                    when: "1d"
                },
                {
                    image: source,
                    alt: "alt",
                    status: "bg-warning",
                    bold:false,
                    message: "Last month's report looks great, I am very happy with the progress so far, keep up the good work!",
                    from: "Morgan Alvarez",
                    when: "2d"
                },
                {
                    image: source,
                    alt: "alt",
                    status: "bg-success",
                    bold:false,
                    message: "Am I a good boy? The reason I ask is because someone told me that people say this to all dogs, even if they aren't good...",
                    from: "Chicken the Dog",
                    when: "2d"
                }
            ]
        };
    }


    render() {
        const messages = this.state.messages && (this.state.messages.map((o, index) => {
            return (<ToolbarNavDropdownMessageItem image={o.image} alt={o.alt} status={o.status} bold={o.bold} message={o.message} from={o.from} when={o.when} key={index} />);
        }).concat());

        return (
            <ToolbarNavDropdown icon={["fas", "envelope"]} count={this.state.messages.length}>
                <div className="dropdown-list dropdown-menu dropdown-menu-right shadow animated--grow-in" style={{display:"block"}}>
                    <h6 className="dropdown-header">
                        Message Center
                    </h6>
                    {messages}
                    <a className="dropdown-item text-center small text-gray-500" href="#">Read More Messages</a>
                </div>
            </ToolbarNavDropdown>
        );
    }
}