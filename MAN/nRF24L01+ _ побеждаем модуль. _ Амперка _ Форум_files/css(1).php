@charset "UTF-8";

/* --- bb_code.css --- */

/* .bbCodeX classes are designed to exist inside .baseHtml. ie: they have no CSS reset applied */

.bbCodeBlock
{
	margin: 1em 140px 1em 0;
border: 1px solid #d7edfc;
-webkit-border-radius: 5px; -moz-border-radius: 5px; -khtml-border-radius: 5px; border-radius: 5px;
overflow: auto;

}

	.bbCodeBlock .bbCodeBlock,
	.hasJs .bbCodeBlock .bbCodeSpoilerText,
	.messageList.withSidebar .bbCodeBlock
	{
		margin-right: 0;
	}

	/* mini CSS reset */
	.bbCodeBlock pre,
	.bbCodeBlock blockquote
	{
		margin: 0;
	}
	
	.bbCodeBlock img
	{
		border: none;
	}

.bbCodeBlock .type
{
	font-size: 11px;
font-family: 'Roboto', sans-serif;
color: #6cb2e4;
background-color: #d7edfc;
padding: 3px 8px;
border-bottom: 1px solid #a5cae4;
-webkit-border-top-left-radius: 4px; -moz-border-radius-topleft: 4px; -khtml-border-top-left-radius: 4px; border-top-left-radius: 4px;
-webkit-border-top-right-radius: 4px; -moz-border-radius-topright: 4px; -khtml-border-top-right-radius: 4px; border-top-right-radius: 4px;

}

.bbCodeBlock pre,
.bbCodeBlock .code
{
	font-size: 10pt;
font-family: Consolas, 'Courier New', Courier, monospace;
background: #f0f7fc url('styles/default/xenforo/gradients/category-23px-light.png') repeat-x top;
padding: 10px;
-webkit-border-radius: 5px; -moz-border-radius: 5px; -khtml-border-radius: 5px; border-radius: 5px;
word-wrap: normal;
overflow: auto;
line-height: 1.24;
min-height: 30px;
max-height: 500px;
_width: 600px;
direction: ltr;

}

.bbCodeBlock .code
{
	white-space: nowrap;
}

.bbCodeQuote
{
	border-width: 0;
border-left-width: 5px;
border-left-color: rgb(200,200,200);
-webkit-border-radius: 0; -moz-border-radius: 0; -khtml-border-radius: 0; border-radius: 0;
overflow: auto;

}

.bbCodeQuote .attribution
{
	color: rgb(20,20,20);
background-color: rgb(243, 243, 243);
border-bottom: 1px solid rgb(255, 255, 255);

}

.bbCodeQuote .quoteContainer
{
	overflow: hidden;
	position: relative;
	
	font-style: italic;
font-size: 14px;
font-family: Georgia, 'Times New Roman', serif;
color: rgb(100,100,100);
background-color: rgb(250, 250, 250);
padding: 10px 10px 10px 45px;

}


	.bbCodeQuote .quoteContainer .quote
	{
		max-height: 150px;
		overflow: hidden;
		padding-bottom: 1px;
	}
	
		.NoJs .bbCodeQuote .quoteContainer .quote
		{
			max-height: none;
		}

	.bbCodeQuote .quoteContainer .quoteExpand
	{		
		display: none;
		-webkit-box-sizing: border-box; -moz-box-sizing: border-box; -ms-box-sizing: border-box; box-sizing: border-box;
		position: absolute;
		height: 80px;
		top: 90px;
		left: 0;
		right: 0;
		
		font-size: 11px;
		line-height: 1;
		text-align: center;
		color: #f9bc6d;
		cursor: pointer;
		padding-top: 65px;
		background: -webkit-linear-gradient(top, rgba(250, 250, 250, 0) 0%, rgb(250, 250, 250) 80%);
		background: -moz-linear-gradient(top, rgba(250, 250, 250, 0) 0%, rgb(250, 250, 250) 80%);
		background: -o-linear-gradient(top, rgba(250, 250, 250, 0) 0%, rgb(250, 250, 250) 80%);
		background: linear-gradient(to bottom, rgba(250, 250, 250, 0) 0%, rgb(250, 250, 250) 80%);
		
		border-bottom-left-radius: ;
		border-bottom-right-radius: ;
	}
	
	.bbCodeQuote .quoteContainer .quoteExpand.quoteCut
	{
		display: block;
	}
	
	.bbCodeQuote .quoteContainer.expanded .quote
	{
		max-height: none;
	}
	
	.bbCodeQuote .quoteContainer.expanded .quoteExpand
	{
		display: none;
	}


	.bbCodeQuote img
	{
		max-height: 150px;
	}
	
	.bbCodeQuote iframe,
	.bbCodeQuote object,
	.bbCodeQuote embed
	{
		max-width: 200px;
		max-height: 150px;
	}
	
	.bbCodeQuote iframe:-webkit-full-screen
	{
		max-width: none;
		max-height: none;
	}
	
	.bbCodeQuote iframe:-moz-full-screen
	{
		max-width: none;
		max-height: none;
	}
	
	.bbCodeQuote iframe:-ms-fullscreen
	{
		max-width: none;
		max-height: none;
	}
	
	.bbCodeQuote iframe:fullscreen
	{
		max-width: none;
		max-height: none;
	}
	
.bbCodeSpoilerButton
{
	margin: 5px 0;
	max-width: 99%;
}

	.bbCodeSpoilerButton > span
	{
		display: inline-block;
		max-width: 100%;
		white-space: nowrap;
		text-overflow: ellipsis;
		overflow: hidden;
	}
	
.hasJs .bbCodeSpoilerText
{
	display: none;
	background-color: #f0f7fc;
padding: 5px;
margin-top: 5px;
margin-right: 140px;
margin-bottom: 5px;
border: 1px solid #d7edfc;
-webkit-border-radius: 5px; -moz-border-radius: 5px; -khtml-border-radius: 5px; border-radius: 5px;
overflow: auto;

}

	.hasJs .bbCodeSpoilerText .bbCodeSpoilerText,
	.hasJs .bbCodeSpoilerText .bbCodeBlock,
	.hasJs .messageList.withSidebar .bbCodeSpoilerText
	{
		margin-right: 0;
	}
	
.NoJs .bbCodeSpoilerContainer
{
	background-color: rgb(20,20,20); /* fallback for browsers without currentColor */
	background-color: currentColor;
}

	.NoJs .bbCodeSpoilerContainer > .bbCodeSpoilerText
	{
		visibility: hidden;
	}

	.NoJs .bbCodeSpoilerContainer:hover
	{
		background-color: transparent;
	}
	
		.NoJs .bbCodeSpoilerContainer:hover > .bbCodeSpoilerText
		{
			visibility: visible;
		}


@media (max-width:800px)
{
	.Responsive .bbCodeBlock,
	.Responsive.hasJs .bbCodeSpoilerText
	{
		margin-right: 0;
	}
}
.bbCodePHP ol,
.bbCodeHtml ol,
.bbCodeCode ol {
	color: lightgrey;
	-moz-user-select: -moz-none;
	-khtml-user-select: none;
	-webkit-user-select: none;
	-ms-user-select: none;
	user-select: none;
}

.bbCodePHP li > div,
.bbCodeHtml li > div,
.bbCodeCode li > div {
	color: grey;
	-moz-user-select: text;
	-khtml-user-select: text;
	-webkit-user-select: text;
	-ms-user-select: text;
	user-select: text;
}

/* --- bbm_buttons.css --- */

span.mce_bbm_hl {background-position:-760px 0 !important}
span.mce_bbm_raw {background-position:-260px 0 !important}
span.mce_bbm_spoiler {
	background:url(styles/sedo/editor/adv_sprites.png) no-repeat 0 0 !important;
}

/* --- likes_summary.css --- */

.likesSummary
{
	overflow: hidden; zoom: 1;
	font-size: 11px;
}

	.LikeText
	{
		float: left;
	}
	
	.likeInfo
	{
		float: right;
	}

/* --- login_bar.css --- */

/** Login bar basics **/

#loginBar
{
	color: #a5cae4;
background-color: #032A46;
display: inline-block;
position: relative;
z-index: 1;

}

	#loginBar .ctrlWrapper
	{
		margin: 0 10px;
	}

	#loginBar .pageContent
	{
		padding-top: 0px;
		position: relative;
		_height: 0px;
	}

	#loginBar a
	{
		color: #6cb2e4;

	}

	#loginBar form
	{
		padding: 5px 0;
margin: 0 auto;
display: none;
line-height: 20px;
position: relative;
text-align: left;
z-index: 1;

	}
	
		#loginBar .xenForm .ctrlUnit,		
		#loginBar .xenForm .ctrlUnit > dt label
		{
			margin: 0;
			border: none;
		}
	
		#loginBar .xenForm .ctrlUnit > dd
		{
			position: relative;
		}
	
	#loginBar .lostPassword,
	#loginBar .lostPasswordLogin
	{
		font-size: 11px;
	}
	
	#loginBar .rememberPassword
	{
		font-size: 11px;
	}

	#loginBar .textCtrl
	{
		color: #f0f7fc;
background-color: #2b485c;
border-color: #65a5d1;

	}
	
	#loginBar .textCtrl[type=text]
	{
		font-weight: bold;
font-size: 18px;

	}

	#loginBar .textCtrl:-webkit-autofill /* http://code.google.com/p/chromium/issues/detail?id=1334#c35 */
	{
		background: #2b485c !important;
		color: #f0f7fc;
	}

	#loginBar .textCtrl:focus
	{
		background: black none;

	}
	
	#loginBar input.textCtrl.disabled
	{
		color: #a5cae4;
background-color: #032A46;
border-style: dashed;

	}
	
	#loginBar .button
	{
		min-width: 180px;
		*width: 180px;
	}
	
		#loginBar .button.primary
		{
			font-weight: bold;
		}
		
/** changes when eAuth is present **/

#loginBar form.eAuth
{
	-x-max-width: 700px; /* normal width + 170px */
}

	#loginBar form.eAuth .ctrlWrapper
	{
		border-right: 1px dotted #176093;
		margin-right: 200px;
		-webkit-box-sizing: border-box; -moz-box-sizing: border-box; -ms-box-sizing: border-box; box-sizing: border-box;
	}

	#loginBar form.eAuth #eAuthUnit
	{
		position: absolute;
		top: 0px;
		right: 10px;
	}

		#eAuthUnit li
		{
			margin-top: 10px;
			line-height: 0;
		}
	
/** handle **/

#loginBar #loginBarHandle
{
	font-size: 11px;
color: #f0f7fc;
background-color: #032A46;
padding: 40px 10px 0;
margin-right: 150px;
-webkit-border-bottom-right-radius: 10px; -moz-border-radius-bottomright: 10px; -khtml-border-bottom-right-radius: 10px; border-bottom-right-radius: 10px;
-webkit-border-bottom-left-radius: 10px; -moz-border-radius-bottomleft: 10px; -khtml-border-bottom-left-radius: 10px; border-bottom-left-radius: 10px;
position: absolute;
right: 0px;
bottom: -20px;
text-align: center;
z-index: 1;
line-height: 20px;
-webkit-box-shadow: 0px 2px 5px #032A46; -moz-box-shadow: 0px 2px 5px #032A46; -khtml-box-shadow: 0px 2px 5px #032A46; box-shadow: 0px 2px 5px #032A46;
width: 180px;

}


@media (max-width:800px)
{
	.Responsive #loginBar form.eAuth .ctrlWrapper
	{
		border-right: none;
		margin-right: 10px;
	}

	.Responsive #loginBar form.eAuth #eAuthUnit
	{
		position: static;
		width: 180px;
		margin: 0 auto 10px;
	}
}


/* --- message.css --- */



.messageList
{
	
}

.messageList .message
{
	padding: 21px;
margin-top: 14px;
margin-bottom: 14px;
border-top: 1px dashed #f60;

}

/* clearfix */ .messageList .message { zoom: 1; } .messageList .message:after { content: '.'; display: block; height: 0; clear: both; visibility: hidden; }

/*** Message block ***/

.message .messageInfo
{
	padding: 0;
margin-left: 140px;
border-bottom: 1px none black;

	zoom: 1;
}

	.message .newIndicator
	{
		font-size: 11px;
color: #fff4e5;
background-color: #f9bc6d;
padding: 1px 5px;
margin: -5px -5px 5px 5px;
border: 1px solid #f9d9b0;
-webkit-border-radius: 3px; -moz-border-radius: 3px; -khtml-border-radius: 3px; border-radius: 3px;
-webkit-border-top-right-radius: 0px; -moz-border-radius-topright: 0px; -khtml-border-top-right-radius: 0px; border-top-right-radius: 0px;
display: block;
float: right;
position: relative;

		
		margin-right: -5px;
	}
	
		.message .newIndicator span
		{
			background-color: #6cb2e4;
-webkit-border-top-right-radius: 3px; -moz-border-radius-topright: 3px; -khtml-border-top-right-radius: 3px; border-top-right-radius: 3px;
display: none;
position: absolute;
top: -4px;
right: -1px;
width: 5px;
height: 4px;

		}

	.message .messageContent
	{
		padding-bottom: 2px;
min-height: 100px;
overflow: hidden;
*zoom: 1;

	}
	
	.message .messageTextEndMarker
	{
		height: 0;
		font-size: 0;
		overflow; hidden;
	}
	
	.message .editDate
	{
		text-align: right;
		margin-top: 5px;
		font-size: 11px;
		color: rgb(150,150,150);
	}

	.message .signature
	{
		font-size: 11px;
color: rgb(150,150,150);
padding: 0 0 0 5px;
margin-top: 14px;
border-left: 5px solid rgb(200,200,200);

	}

	.message .messageMeta
	{
		font-size: 11px;
padding: 15px 5px 5px;
margin: -5px;
overflow: hidden;
zoom: 1;

	}

		.message .privateControls
		{
			float: left;

		}

		.message .publicControls
		{
			float: right;

		}
		
			.message .privateControls .item
			{
				margin-right: 10px;
				float: left;
			}

				.message .privateControls .item:last-child
				{
					margin-right: 0;
				}

			.message .publicControls .item
			{
				margin-left: 10px;
				float: left;
			}
	
				.message .messageMeta .control
				{
					
				}
				
					.message .messageMeta .control:focus
					{
						
					}
				
					.message .messageMeta .control:hover
					{
						
					}
				
					.message .messageMeta .control:active
					{
						
					}
	/*** multiquote +/- ***/
			
	.message .publicControls .MultiQuoteControl
	{
		padding-left: 4px;
		padding-right: 4px;
		-webkit-border-radius: 2px; -moz-border-radius: 2px; -khtml-border-radius: 2px; border-radius: 2px;
		margin-left: 6px;
		margin-right: -4px;
	}
	
	
	.message .publicControls .MultiQuoteControl.active
	{
		background-color: #d7edfc;
	}
	
		.messageNotices li
	{
		font-size: 11px;
background: #f9d9b0 url('styles/default/xenforo/gradients/form-button-white-25px.png') repeat-x top;
padding: 5px;
margin: 10px 0;
border: 1px solid #f9d9b0;
-webkit-border-radius: 5px; -moz-border-radius: 5px; -khtml-border-radius: 5px; border-radius: 5px;
line-height: 16px;

	}
	
		.messageNotices .icon
		{
			float: right;
			width: 16px;
			height: 16px;
			background: url('styles/default/xenforo/xenforo-ui-sprite.png') no-repeat 1000px 1000px;
		}
	
			.messageNotices .warningNotice .icon { background-position: -48px -32px; }		
			.messageNotices .deletedNotice .icon { background-position: -64px -32px; }		
			.messageNotices .moderatedNotice .icon {background-position: -32px -16px; }
	
	.message .likesSummary
	{
		margin-top: 10px;
border-left: 5px solid rgb(215, 46, 49);

	}
	
	.message .messageText > *:first-child
	{
		margin-top: 0;
	}

/* inline moderation changes */

.InlineModChecked .messageUserBlock,
.InlineModChecked .messageInfo,
.InlineModChecked .messageNotices,
.InlineModChecked .bbCodeBlock .type,
.InlineModChecked .bbCodeBlock blockquote,
.InlineModChecked .attachedFiles .attachedFilesHeader,
.InlineModChecked .attachedFiles .attachmentList
{
	background: rgb(255, 255, 200) url('styles/default/xenforo/gradients/category-23px-light.png') repeat-x top;

}

.InlineModChecked .messageUserBlock div.avatarHolder,
.InlineModChecked .messageUserBlock .extraUserInfo
{
	background: transparent;
}

.InlineModChecked .messageUserBlock .arrow span
{
	border-left-color: rgb(255, 255, 200);
}

/* message list */

.messageList .newMessagesNotice
{
	margin: 10px auto;
	padding: 5px 10px;
	-webkit-border-radius: 5px; -moz-border-radius: 5px; -khtml-border-radius: 5px; border-radius: 5px;
	border: 1px solid #a5cae4;
	background: #d7edfc url(styles/default/xenforo/gradients/category-23px-light.png) repeat-x top;
	font-size: 11px;
}

/* deleted / ignored message placeholder */

.messageList .message.placeholder
{
}

.messageList .placeholder .placeholderContent
{	
	overflow: hidden; zoom: 1;
	color: #65a5d1;
	font-size: 11px;
}

	.messageList .placeholder a.avatar
	{
		float: left;
		display: block;
	}
	
		.messageList .placeholder a.avatar img
		{
			display: block;
			width: 32px;
			height: 32px;
		}
		
	.messageList .placeholder .privateControls
	{
		margin-top: -5px;
	}
	

/* messages remaining link */

.postsRemaining a,
a.postsRemaining
{
	font-size: 11px;
	color: rgb(150,150,150);
}


@media (max-width:800px)
{
	.Responsive .message .newIndicator
	{
		margin-right: 0;
		-webkit-border-top-right-radius: 3px; -moz-border-radius-topright: 3px; -khtml-border-top-right-radius: 3px; border-top-right-radius: 3px;
	}
	
		.Responsive .message .newIndicator span
		{
			display: none;
		}
}

@media (max-width:480px)
{
	.Responsive .message .messageInfo
	{
		margin-left: 0;
		padding: 0 10px;
	}

	.Responsive .message .messageContent
	{
		min-height: 0;
	}	

	.Responsive .message .newIndicator
	{
		margin-right: -5px;
		margin-top: -16px;
	}

	.Responsive .message .postNumber,
	.Responsive .message .authorEnd
	{
		display: none;
	}
	
	.Responsive .message .signature
	{
		display: none;
	}
	
	.Responsive .messageList .placeholder a.avatar
	{
		margin-right: 10px;
	}
}


/* --- message_user_info.css --- */

.messageUserInfo
{
	float: left;
width: 124px;

}

	.messageUserBlock
	{
		
		
		position: relative;
	}
		
		.messageUserBlock div.avatarHolder
		{
			-webkit-border-radius: 4px; -moz-border-radius: 4px; -khtml-border-radius: 4px; border-radius: 4px;

			
			position: relative;	
		}
		
			.messageUserBlock div.avatarHolder .avatar
			{
				display: block;
				font-size: 0;
			}
			
			.messageUserBlock div.avatarHolder .onlineMarker
			{
				position: absolute;
				top: -1px;
				left: -1px;
				
				border: 7px solid transparent;
border-top-color: rgb(127, 185, 0);
border-left-color: rgb(127, 185, 0);
-webkit-border-top-left-radius: 5px; -moz-border-radius-topleft: 5px; -khtml-border-top-left-radius: 5px; border-top-left-radius: 5px;
-webkit-border-top-right-radius: 3px; -moz-border-radius-topright: 3px; -khtml-border-top-right-radius: 3px; border-top-right-radius: 3px;
-webkit-border-bottom-left-radius: 3px; -moz-border-radius-bottomleft: 3px; -khtml-border-bottom-left-radius: 3px; border-bottom-left-radius: 3px;

			}
			
		.messageUserBlock h3.userText
		{
			padding: 6px;

		}
		
		.messageUserBlock .userBanner
		{
			display: block;
			margin-bottom: 5px;
			margin-left: -12px;
			margin-right: -12px;
		}
		
		.messageUserBlock .userBanner:last-child
		{
			margin-bottom: 0;
		}
	
		.messageUserBlock a.username
		{
			font-weight: bold;
display: block;
overflow: hidden;
line-height: 16px;

			
		}
		
		.messageUserBlock .userTitle
		{
			font-size: 11px;
display: block;

		}
		
		.messageUserBlock .extraUserInfo
		{
			font-size: 10px;
background-color: #f0f7fc;
padding: 4px 6px;
-webkit-border-radius: 4px; -moz-border-radius: 4px; -khtml-border-radius: 4px; border-radius: 4px;

		}
		
			.messageUserBlock .extraUserInfo dl
			{
				margin: 2px 0 0;
			}
							
			.messageUserBlock .extraUserInfo img
			{
				max-width: 100%;
			}
		
		.messageUserBlock .arrow
		{
			position: absolute;
			top: 10px;
			right: -10px;
			
			display: block;
			width: 0px;
			height: 0px;
			line-height: 0px;
			
			border: 10px solid transparent;
			border-left-color: ;
			-moz-border-left-colors: ;
			border-right: none;
			
			/* Hide from IE6 */
			_display: none;
		}
		
			.messageUserBlock .arrow span
			{
				position: absolute;
				top: -10px;
				left: -11px;
				
				display: block;
				width: 0px;
				height: 0px;
				line-height: 0px;
				
				border: 10px solid transparent;
				border-left-color: ;
				-moz-border-left-colors: ;
				border-right: none;
			}


@media (max-width:480px)
{
	.Responsive .messageUserInfo
	{
		float: none;
		width: auto; 
	}

	.Responsive .messageUserBlock
	{
		overflow: hidden;
		margin-bottom: 5px;
		position: relative;
	}

	.Responsive .messageUserBlock div.avatarHolder
	{
		float: left;
		padding: 5px;
	}

		.Responsive .messageUserBlock div.avatarHolder .avatar img
		{
			width: 48px;
			height: 48px;
		}
		
		.Responsive .messageUserBlock div.avatarHolder .onlineMarker
		{
			top: 4px;
			left: 4px;
			border-width: 6px;
		}

	.Responsive .messageUserBlock h3.userText
	{
		margin-left: 64px;
	}
	
	.Responsive .messageUserBlock .userBanner
	{
		max-width: 150px;
		margin-left: 0;
		margin-right: 0;
		-webkit-border-top-left-radius: 3px; -moz-border-radius-topleft: 3px; -khtml-border-top-left-radius: 3px; border-top-left-radius: 3px;
		-webkit-border-top-right-radius: 3px; -moz-border-radius-topright: 3px; -khtml-border-top-right-radius: 3px; border-top-right-radius: 3px;
		position: static;
		display: inline-block;
	}
	
		.Responsive .messageUserBlock .userBanner span
		{
			display: none;
		}

	.Responsive .messageUserBlock .extraUserInfo
	{
		display: none;
	}

	.Responsive .messageUserBlock .arrow
	{
		display: none;
	}
}


/* --- thread_view.css --- */

.thread_view .threadAlerts
{
	border: 1px solid #d7edfc;
	-webkit-border-radius: 5px; -moz-border-radius: 5px; -khtml-border-radius: 5px; border-radius: 5px;
	font-size: 11px;
	margin: 10px 0;
	padding: 5px;
	line-height: 16px;
	background-image: url('styles/default/xenforo/gradients/form-button-white-25px.png');
}
	
	.thread_view .threadAlerts dt
	{
		color: #6cb2e4;
		display: inline;
	}
	
	.thread_view .threadAlerts dd
	{
		color: #2b485c;
		font-weight: bold;
		display: inline;
	}
	
		.thread_view .threadAlerts .icon
		{
			float: right;
			width: 16px;
			height: 16px;
			margin-left: 5px;
			background: url('styles/default/xenforo/xenforo-ui-sprite.png') no-repeat -1000px -1000px;
		}
		
			.thread_view .threadAlerts .deletedAlert .icon { background-position: -64px -32px; }
			.thread_view .threadAlerts .moderatedAlert .icon { background-position: -32px -16px; }
			.thread_view .threadAlerts .lockedAlert .icon { background-position: -16px -16px; }
	
.thread_view .threadAlerts + * > .messageList
{
	border-top: none;
}

.thread_view .threadNotices
{
	background-color: #f0f7fc;
	border: 1px solid #a5cae4;
	-webkit-border-radius: 5px; -moz-border-radius: 5px; -khtml-border-radius: 5px; border-radius: 5px;
	padding: 10px;
	margin: 10px auto;
}

.thread_view .InlineMod
{
	overflow: hidden; zoom: 1;
}
