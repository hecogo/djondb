var mongo = new Mongo('localhost');
var db = mongo.getDB("myamazon");

// The only user in our DB
//
db.users.insert({
	name: "Phil",
	lastName: "Collins",
	username: "pcollins"
});


db.users.balance.insert({
	username: "pcollins",
	description: "founded account",
	value: 100
});

// Creating the products
//

db.products.insert({ 
	name: "Everything Jacqueline Kennedy Onassis Book: A portrait of an American icon (Everything Profiles)", 
	type: "History/America",
	author: "Kathleen Tracy", 
	price: 14.95, 
	description: "Jacqueline Lee Bouvier Kennedy Onassis-better known as Jackie O. to the tabloids, \"the deb\" to the Kennedy clan, and the 35th First Lady to historians-is easily one of the most recognizable Presidential wives. She remains the model of the proper American woman. But what was Jackie O. hiding behind those big, dark shades?", 
	details: {
		Paperback: "304 pages",
	   Publisher: { 
		   name: "Adams Media", 
	      date: ISODate("2008-05-01")
	   }
	}
});

db.products.insert({ 
	name: "Incidents in the Life of a Slave Girl (An African American Heritage Book)",
	type: "History/America",
	author: "Linda Brent", 
	price: 16.99, 
	description: "Here is one of the few slave narratives written by a women. Slavery is a terrible thing, but it is far more terrible and harrowing for women than for men. Harriet Jacobs was owned by a brutal master who beat his slaves regularly and subjected them to indignations that were far worse. Jacobs eventually escaped her master and moved to a northern state. Though she was unable to take her children with her at the time they were later reunited. Read her powerful and compelling story.",
	details: {
		Hardcover: "144 pages",
	   Publisher: { 
		   name: "Wilder Publications", 
	      date: ISODate("2008-05-15")
	   }
	}
});

/*
db.products.insert({ 
	name: "",
	type: "",
	author: "", 
	price: 16.99, 
	description: "",
	details: {
		Hardcover: " pages",
	   Publisher: { 
		   name: "", 
	      date: ISODate("--")
	   }
	}
});
*/

db.products.insert({ 
	name: "Adventures of Sherlock Holmes",
	type: "History",
	author: "Arthur Conan Doyle", 
	price: 24.99, 
	description: "This is a pre-1923 historical reproduction that was curated for quality. Quality assurance was conducted on each of these books in an attempt to remove books with imperfections introduced by the digitization process. Though we have made best efforts - the books may have occasional errors that do not impede the reading experience. We believe this work is culturally important and have elected to bring the book back into print as part of our continuing commitment to the preservation of printed works worldwide. This text refers to the Bibliobazaar edition.",
	details: {
		Paperback: "348 pages",
	   Publisher: { 
		   name: "BiblioBazaar", 
	      date: ISODate("2009-05-20")
	   }
	}
});

db.products.insert({ 
	name: "Always Know What To Say - Easy Ways To Approach And Talk To Anyone",
	type: "Business & Investment/Job Hunting & Careers",
	author: "Peter W. Murphy", 
	price: 0, 
	description: "Want to know the easy way to approach and make conversation with new people? In this book you`ll discover simple ways to ensure you always have something interesting to talk about. \n \
	\n \
	Find out how popular people make it look so easy and how you can do the same. \n \
	\n \
	This short 17 page book covers the following strategies:\n \
	\n \
	- How to Approach Someone to Start a Conversation\n \
	- 9 Great Ways to Confidently Approach Anyone\n \
	- How to Stop Feeling Nervous When Meeting New People\n \
	- What to Say When Introducing Yourself to New People \n \
	- 6 Easy Ways to Avoid Getting Stuck for Words\n \
	- 10 Interesting Topics of Conversation for Every Occasion\n \
	- The Best Questions to Keep a Conversation Going\n \
	- How to Shine in Conversation with Listening Skills\n \
	- How to Use Body Language to Read People Like a Book\n \
	- Show People You Like Them and Make Friends with Ease\n \
	\n \
	Start reading this book right away and you`ll enjoy better conversation skills and have much more fun talking to the people in your day to day life.",
	details: {
	   Publisher: { 
		   name: "Amazon Digital Services", 
	   }
	}
});


db.products.insert({ 
	name: "Pride and Prejudice (Penguin Classics)",
	type: "Literature & Fiction/British",
	author: "Jane Austen", 
	price: 11.50, 
	description: "When Elizabeth Bennet first meets eligible bachelor Fitzwilliam Darcy, she thinks him arrogant and conceited; he is indifferent to her good looks and lively mind. When she later discovers that Darcy has involved himself in the troubled relationship between his friend Bingley and her beloved sister Jane, she is determined to dislike him more than ever. In the sparkling comedy of manners that follows, Jane Austen shows the folly of judging by first impressions and superbly evokes the friendships,gossip and snobberies of provincial middle-class life.",
	details: {
		Hardcover: "480 pages",
	   Publisher: { 
		   name: "Penguin Classics Hardcover; Exclusive to Waterstones ed edition", 
	      date: ISODate("2009-10-27")
	   }
	},
	editorialReview: "\"It is a truth universally acknowledged, that a single man in possession of a good fortune, must be in want of a wife.\" \n \
	Next to the exhortation at the beginning of Moby-Dick, \"Call me Ishmael,\" the first sentence of Jane Austen's Pride and Prejudice must be among the most quoted in literature. And certainly what Melville did for whaling Austen does for marriage--tracing the intricacies (not to mention the economics) of 19th-century British mating rituals with a sure hand and an unblinking eye. As usual, Austen trains her sights on a country village and a few families--in this case, the Bennets, the Philips, and the Lucases. Into their midst comes Mr. Bingley, a single man of good fortune, and his friend, Mr. Darcy, who is even richer. Mrs. Bennet, who married above her station, sees their arrival as an opportunity to marry off at least one of her five daughters. Bingley is complaisant and easily charmed by the eldest Bennet girl, Jane; Darcy, however, is harder to please. Put off by Mrs. Bennet's vulgarity and the untoward behavior of the three younger daughters, he is unable to see the true worth of the older girls, Jane and Elizabeth. His excessive pride offends Lizzy, who is more than willing to believe the worst that other people have to say of him; when George Wickham, a soldier stationed in the village, does indeed have a discreditable tale to tell, his words fall on fertile ground. \n \
	\
	Having set up the central misunderstanding of the novel, Austen then brings in her cast of fascinating secondary characters: Mr. Collins, the sycophantic clergyman who aspires to Lizzy's hand but settles for her best friend, Charlotte, instead; Lady Catherine de Bourgh, Mr. Darcy's insufferably snobbish aunt; and the Gardiners, Jane and Elizabeth's low-born but noble-hearted aunt and uncle. Some of Austen's best comedy comes from mixing and matching these representatives of different classes and economic strata, demonstrating the hypocrisy at the heart of so many social interactions. And though the novel is rife with romantic misunderstandings, rejected proposals, disastrous elopements, and a requisite happy ending for those who deserve one, Austen never gets so carried away with the romance that she loses sight of the hard economic realities of 19th-century matrimonial maneuvering. Good marriages for penniless girls such as the Bennets are hard to come by, and even Lizzy, who comes to sincerely value Mr. Darcy, remarks when asked when she first began to love him: \"It has been coming on so gradually, that I hardly know when it began. But I believe I must date it from my first seeing his beautiful grounds at Pemberley.\" She may be joking, but there's more than a little truth to her sentiment, as well. Jane Austen considered Elizabeth Bennet \"as delightful a creature as ever appeared in print\". Readers of Pride and Prejudice would be hard-pressed to disagree. --Alix Wilber --This text refers to an out of print or unavailable edition of this title."
});




