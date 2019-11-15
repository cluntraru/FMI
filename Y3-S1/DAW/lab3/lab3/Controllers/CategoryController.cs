using lab3.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace lab3.Controllers
{
    public class CategoryController : Controller
    {
        private ArticleDBContext db = new ArticleDBContext();
        // GET: Category
        public ActionResult Index()
        {
            var articles = db.Articles.Include("Category");
            ViewBag.Articles = articles;
            return View();
        }

        public ActionResult Show(int id) {
            Article article = db.Articles.Find(id);
            ViewBag.Article = article;
            ViewBag.Category = ;
            return View();
        }

        public ActionResult New() {
            var categories = from cat in db.Categories select cat;
            ViewBag.Categories = categories;
            return View();
        } 
 
        [HttpPost]
        public ActionResult New(Article article) {
            //TODO
        } 
  
        
    }
}